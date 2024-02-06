#include "Scene/Scene.h"

#include "Component/Component.h"
#include "Render/Renderer.h"
#include "Core/Assert.h"
#include "Core/CameraController.h"

#include <unordered_map>
#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_contact.h"
#include "Physics/ActorData.h"
#include "Physics/ContactListener.h"

// Script
#include "Script/ScriptEngine.h"
#include "Script/ScriptInstance.h"
#include "Script/Event/ScriptEventDispatcher.h"
// #include "Script/ScriptCore.h"

// Event
#include "Event/Input.h"
#include "Event/PhysicsEvent.h"
#include "Event/EventDispatcher.h"

GameEngine::Scene::Scene()
    : physicsWorld(nullptr)
    , contactListener(nullptr)
    , scriptEngine(nullptr)
{
}

GameEngine::Scene::~Scene()
{
    if (this->physicsWorld != nullptr)
    {
        delete this->physicsWorld;
        this->physicsWorld = nullptr;
    }
    if (this->contactListener != nullptr)
    {
        delete this->contactListener;
        this->contactListener = nullptr;
    }
}

void GameEngine::Scene::unpdateRuntimeScene(float deltaTime)
{
    //Script
    this->registry.view<GameEngine::ScriptComponent>().each([=](entt::entity entity, ScriptComponent& scriptComponent)
    {
        if (scriptComponent.instance != nullptr)
            scriptComponent.instance->update(deltaTime);
    });

    //physics
    {
        constexpr int32_t velocityIterations = 6;
        constexpr int32_t positionIterations = 2;
        this->physicsWorld->Step(deltaTime, velocityIterations, positionIterations);

        auto view = this->registry.view<GameEngine::Rigidbody2DComponent>();
        for (entt::entity entity: view)
        {
            GameEngine::Actor actor = {entity, this};
            GameEngine::TransformComponent& transformComponent = actor.getComponent<GameEngine::TransformComponent>();
            GameEngine::Rigidbody2DComponent& rigidbody2DComponent = actor.getComponent<GameEngine::Rigidbody2DComponent>();

            b2Body* body = (b2Body*)rigidbody2DComponent.runtimeBody;
            const b2Vec2& position = body->GetPosition();
            transformComponent.translation.x = position.x;
            transformComponent.translation.y = position.y;
            transformComponent.rotation.z = body->GetAngle();
        }
    }
    
    //render setting
    {
        auto viewOfCamera = this->registry.view<GameEngine::TransformComponent, GameEngine::CameraComponent>();
        for (entt::entity entityID: viewOfCamera)
        {
            auto [transformComponent, cameraComponent] = viewOfCamera.get<GameEngine::TransformComponent, GameEngine::CameraComponent>(entityID);
            if (cameraComponent.primary)
            {
                GameEngine::cameraController->setViewTarget(&cameraComponent, &transformComponent);
                break;
            }
        }
    }
}

void GameEngine::Scene::render()
{
    auto view = this->registry.view<GameEngine::TransformComponent, GameEngine::MeshComponent>();

    for (entt::entity entity: view)
    {
        auto [transform, mesh] = view.get<GameEngine::TransformComponent, GameEngine::MeshComponent>(entity);
        Renderer::draw(transform.getTransform(), mesh, (int)entity);
    }
}

std::vector<entt::entity> GameEngine::Scene::getAllActors()
{
    auto view = this->registry.view<GameEngine::MeshComponent>();
    std::vector<entt::entity> entities;
    for (entt::entity entity: view)
        entities.push_back(entity);
    return entities;
}

// template<class Component>
// static void copyComponent(entt::registry& src, entt::registry& dst, std::unordered_map<GameEngine::UUID, entt::entity>& entityMap)
// {
//     auto view = src.view<Component>();
//     for (entt::entity entity: view)
//     {
//         GameEngine::UUID& uuid = src.get<GameEngine::IDComponent>(entity).uuid;
//         entt::entity dstEntityID = entityMap[uuid];
//         Component& component = src.get<Component>(entity);
//         dst.emplace_or_replace<Component>(dstEntityID, component);
//     }
// }

template<typename... Component>
static void copyComponent(entt::registry& src, entt::registry& dst, std::unordered_map<GameEngine::UUID, entt::entity>& entityMap)
{
    ([&](){
        auto view = src.view<Component>();
        for (entt::entity entity: view)
        {
            GameEngine::UUID& uuid = src.get<GameEngine::IDComponent>(entity).uuid;
            entt::entity dstEntityID = entityMap[uuid];
            Component& component = src.get<Component>(entity);
            dst.emplace_or_replace<Component>(dstEntityID, component);
        }
    }(), ...);
}

template<typename... Component>
static void copyComponent(GameEngine::ComponentGroup<Component...>, entt::registry& src, entt::registry& dst, std::unordered_map<GameEngine::UUID, entt::entity>& entityMap)
{
    copyComponent<Component...>(src, dst, entityMap);
}

GameEngine::Scene* GameEngine::Scene::copy(GameEngine::Scene* originalScene)
{
    Scene* newScene = new Scene();
    // Actor::bindScene(newScene);
    entt::registry& srcRegistry = originalScene->registry;
    entt::registry& dstRegistry = newScene->registry;
    std::unordered_map<UUID, entt::entity> entityMap;
    
    auto idView = srcRegistry.view<IDComponent>();
    for (entt::entity entity: idView)
    {
        UUID& uuid = srcRegistry.get<IDComponent>(entity).uuid;
        Actor* newActor = newScene->spawnActor<Actor>(uuid);
        entityMap.insert({uuid, (entt::entity)newActor->getID()});
    }

    copyComponent(GameEngine::AllCompnents{}, srcRegistry, dstRegistry, entityMap);

    return newScene;
}

template<typename... Component>
static void copyActorComponents(entt::entity src, entt::entity dst, entt::registry& registry)
{
    ([&](){
        if (!registry.all_of<Component>(src)) //entity has not this component
            return;
        Component& component = registry.get<Component>(src);
        registry.emplace_or_replace<Component>(dst, component);
    }(), ...);
}

template<typename... Component>
static void copyActorComponents(GameEngine::ComponentGroup<Component...>, entt::entity src, entt::entity dst, entt::registry& registry)
{
    copyActorComponents<Component...>(src, dst, registry);
}

entt::entity GameEngine::Scene::copyActor(entt::entity srcEntityID)
{
    entt::entity newEntityID = this->registry.create();
    GameEngine::IDComponent idCommponent;
    this->registry.emplace_or_replace<IDComponent>(newEntityID, idCommponent);
    copyActorComponents(GameEngine::AllCompnents{}, srcEntityID, newEntityID, this->registry);
    return newEntityID;
}

static b2BodyType getBox2DRigidbodyType(GameEngine::Rigidbody2DComponent::BodyType bodyType)
{
    switch (bodyType)
    {
    case GameEngine::Rigidbody2DComponent::BodyType::Static:
        return b2BodyType::b2_staticBody;
    case GameEngine::Rigidbody2DComponent::BodyType::Dynamic:
        return b2BodyType::b2_dynamicBody;
    case GameEngine::Rigidbody2DComponent::BodyType::Kinematic:
        return b2BodyType::b2_kinematicBody;
    default:
        break;
    }

    GAME_ENGINE_ASSERT(false, "Unknow body type");
    return b2BodyType::b2_staticBody;
}

void GameEngine::Scene::onRuntimeStart(const std::string& projectRootPath)
{
    //physics
    this->physicsWorld = new b2World({0.0f, -9.8f});

    auto rigidbody2DView = this->registry.view<GameEngine::Rigidbody2DComponent>();

    for (entt::entity entityID: rigidbody2DView)
    {
        GameEngine::Actor actor = {entityID, this};
        GameEngine::TransformComponent& transformComponent = actor.getComponent<GameEngine::TransformComponent>();
        GameEngine::Rigidbody2DComponent& rigidbody2DComponent = actor.getComponent<GameEngine::Rigidbody2DComponent>();

        b2BodyDef bodyDef;
        bodyDef.type = getBox2DRigidbodyType(rigidbody2DComponent.type);
        bodyDef.position.Set(transformComponent.translation.x, transformComponent.translation.y);
        bodyDef.angle = transformComponent.rotation.z;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(new GameEngine::ActorData(entityID, this));

        b2Body* body = this->physicsWorld->CreateBody(&bodyDef);
        body->SetFixedRotation(rigidbody2DComponent.fixedRotation);
        rigidbody2DComponent.runtimeBody = body;

        if (actor.hasComponent<GameEngine::BoxCollider2DComponent>())
        {
            GameEngine::BoxCollider2DComponent& boxCollider2DComponent = actor.getComponent<GameEngine::BoxCollider2DComponent>();

            b2PolygonShape boxShape;
            boxShape.SetAsBox(boxCollider2DComponent.size.x * transformComponent.scale.x, boxCollider2DComponent.size.y * transformComponent.scale.y
            , b2Vec2(boxCollider2DComponent.offset.x, boxCollider2DComponent.offset.y), 0.0f);

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &boxShape;
            fixtureDef.density = boxCollider2DComponent.density;
            fixtureDef.friction = boxCollider2DComponent.friction;
            fixtureDef.restitution = boxCollider2DComponent.restitution;
            fixtureDef.restitutionThreshold = boxCollider2DComponent.restitutionThreshold;
            
            body->CreateFixture(&fixtureDef);
        }
        
    }

    delete this->contactListener;
    this->contactListener = new GameEngine::ContactListener();
    this->contactListener->setBeginContact([](b2Contact* contact){
        GameEngine::ActorData* a = (GameEngine::ActorData*)(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        GameEngine::ActorData* b = (GameEngine::ActorData*)(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        GameEngine::CollisionEvent collisionEvent(a, b);
        GameEngine::EventDispatcher::trigger(&collisionEvent);
    });
    this->physicsWorld->SetContactListener(this->contactListener);
    
    //script
    
    this->scriptEngine = new GameEngine::Script::ScriptEngine();
    this->scriptEngine->init(this);
    
    auto scriptView = this->registry.view<GameEngine::ScriptComponent>();
    for (entt::entity entityID: scriptView)
    {
        GameEngine::Actor actor = {entityID, this};
        GameEngine::ScriptComponent& scriptComponent = actor.getComponent<GameEngine::ScriptComponent>();
        
        if (scriptComponent.scriptPath.empty())
            continue;
        if (scriptComponent.instance == nullptr)
            scriptComponent.instance = new GameEngine::Script::ScriptInstance();
        this->scriptEngine->setTargetEntityID((uint32_t)entityID);
        this->scriptEngine->load((*scriptComponent.instance), projectRootPath + '/' + scriptComponent.scriptPath);
        scriptComponent.instance->invokeConstructor();
        scriptComponent.instance->begin();
    }
}

void GameEngine::Scene::onRunTimeStop()
{
    // 不能再onRunTimeStart裡面reset，std::funciton必須在dll還在的時候delete
    // GameEngine::EventDispatcher::reset();
    GameEngine::Script::ScriptEventDispatcher::reset();
    delete this->physicsWorld;
    this->physicsWorld = nullptr;
}

void GameEngine::Scene::onViewportResize(float width, float height)
{
    auto cameraComponentView = this->registry.view<GameEngine::CameraComponent>();
    for (entt::entity entityID: cameraComponentView)
    {
        this->queryActorComponent<GameEngine::CameraComponent>(entityID).camera.resize(width, height);
    }
}