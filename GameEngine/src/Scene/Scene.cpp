#include "Scene/Scene.h"

#include "Component/Component.h"
#include "Render/Renderer.h"

#include <unordered_map>

GameEngine::Scene::Scene()
{
}

GameEngine::Scene::~Scene()
{
}

void GameEngine::Scene::unpdateScene(float deltaTime)
{
    this->registry.view<GameEngine::ScriptComponent>().each([=](entt::entity entity, ScriptComponent& scriptComponent)
    {
        scriptComponent.instance->update(deltaTime);
    });
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

GameEngine::Scene* GameEngine::Scene::copy(GameEngine::Scene* other)
{
    Scene* newScene = new Scene();
    Actor::bindScene(newScene);
    entt::registry& srcRegistry = other->registry;
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

    Actor::bindScene(other);
    return newScene;
}

namespace GameEngine
{
    Scene* globalScene = new Scene();
}