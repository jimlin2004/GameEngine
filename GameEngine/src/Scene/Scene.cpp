#include "Scene/Scene.h"

#include "Component/Component.h"
#include "Render/Renderer.h"

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
        Renderer::draw(transform.getTransform(), mesh);
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

namespace GameEngine
{
    Scene* globalScene = new Scene();
}