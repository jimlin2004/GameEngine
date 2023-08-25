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

#include "Script/ScriptEngine.h"
#include "Script/ScriptCore.h"
#include "Event/Input.h"

GameEngine::Scene::Scene()
    : physicsWorld(nullptr)
{
}

GameEngine::Scene::~Scene()
{
    if (this->physicsWorld != nullptr)
    {
        delete this->physicsWorld;
        this->physicsWorld = nullptr;
    }
}

void GameEngine::Scene::unpdateRuntimeScene(float deltaTime)
{
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

template<class Component>
static void copyComponent(entt::registry& src, entt::registry& dst, std::unordered_map<GameEngine::UUID, entt::entity>& entityMap)
{
    auto view = src.view<Component>();
    for (entt::entity entity: view)
    {
        GameEngine::UUID& uuid = src.get<GameEngine::IDComponent>(entity).uuid;
        entt::entity dstEntityID = entityMap[uuid];
        Component& component = src.get<Component>(entity);
        dst.emplace_or_replace<Component>(dstEntityID, component);
    }
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

    copyComponent<TagComponent>(srcRegistry, dstRegistry, entityMap);
    copyComponent<TransformComponent>(srcRegistry, dstRegistry, entityMap);
    copyComponent<MeshComponent>(srcRegistry, dstRegistry, entityMap);
    copyComponent<CameraComponent>(srcRegistry, dstRegistry, entityMap);
    copyComponent<ScriptComponent>(srcRegistry, dstRegistry, entityMap);
    copyComponent<Rigidbody2DComponent>(srcRegistry, dstRegistry, entityMap);
    copyComponent<BoxCollider2DComponent>(srcRegistry, dstRegistry, entityMap);

    // Actor::bindScene(originalScene);
    return newScene;
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

void GameEngine::Scene::onRuntimeStart()
{
    //physics
    this->physicsWorld = new b2World({0.0f, -9.8f});

    auto rigidbody2DView = this->registry.view<GameEngine::Rigidbody2DComponent>();

    for (entt::entity entity: rigidbody2DView)
    {
        GameEngine::Actor actor = {entity, this};
        GameEngine::TransformComponent& transformComponent = actor.getComponent<GameEngine::TransformComponent>();
        GameEngine::Rigidbody2DComponent& rigidbody2DComponent = actor.getComponent<GameEngine::Rigidbody2DComponent>();

        b2BodyDef bodyDef;
        bodyDef.type = getBox2DRigidbodyType(rigidbody2DComponent.type);
        bodyDef.position.Set(transformComponent.translation.x, transformComponent.translation.y);
        bodyDef.angle = transformComponent.rotation.z;

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

    //script
    
    GameEngine::ScriptEngine::init("D:/code/cpp/gameEngine/TestGame/build/lib/GameEngineScript.dll");
    
    auto scriptView = this->registry.view<GameEngine::ScriptComponent>();
    for (entt::entity entityID: scriptView)
    {
        GameEngine::Actor actor = {entityID, this};
        GameEngine::ScriptComponent& scriptComponent = actor.getComponent<GameEngine::ScriptComponent>();
        
        if (scriptComponent.className == "None")
            continue;
        scriptComponent.instance = GameEngine::ScriptEngine::createActor(scriptComponent.className, entityID, this);
        scriptComponent.instance->begin();
    }
}

void GameEngine::Scene::onRunTimeStop()
{
    delete this->physicsWorld;
    this->physicsWorld = nullptr;
}

namespace GameEngine
{
    Scene* globalScene = new Scene();
}