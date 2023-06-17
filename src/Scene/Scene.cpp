#include "Scene/Scene.h"

GameEngine::Scene::Scene()
{

}

GameEngine::Scene::~Scene()
{

}

void GameEngine::Scene::unpdateScene(float deltaTime)
{

}

void GameEngine::Scene::render()
{
    auto view = this->registry.view<GameEngine::TransformComponent, GameEngine::MeshComponent>();

    for (entt::entity entity: view)
    {
        auto [transform, mesh] = view.get<GameEngine::TransformComponent, GameEngine::MeshComponent>(entity);
        Renderer::drawQuad(transform.getTransform(), mesh.color);
    }
}

namespace GameEngine
{
    Scene* globalScene = new Scene();
}