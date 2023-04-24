#include "Scene/Scene.h"

GameEngine::Scene::Scene()
{
    this->sceneGraph = new GameEngine::SceneGraph();
}

GameEngine::Scene::~Scene()
{
    delete this->sceneGraph;
}

void GameEngine::Scene::unpdateScene(float deltaTime)
{
    for (std::pair<const std::string, std::map<std::string, GameEngine::SceneGraphNode*>>& gamebnjectMapPair: this->sceneGraph->sceneMap)
    {
        for (std::pair<const std::string, GameEngine::SceneGraphNode*>& nodePair: gamebnjectMapPair.second)
        {
            nodePair.second->actor->update(deltaTime);
        }
    }
}

void GameEngine::Scene::render()
{
    for (std::pair<const std::string, std::map<std::string, GameEngine::SceneGraphNode*>>& gamebnjectMapPair: this->sceneGraph->sceneMap)
    {
        for (std::pair<const std::string, GameEngine::SceneGraphNode*>& nodePair: gamebnjectMapPair.second)
        {
            nodePair.second->actor->render();
        }
    }
}

template<class TActor>
TActor* GameEngine::Scene::spawnActor(const glm::vec3& position)
{
    TActor* obj = new TActor(position.x, position.y);
    this->sceneGraph->addNode<TActor>(obj);
    return obj;
}

template<class TActor>
TActor* GameEngine::Scene::spawnActor(const glm::vec3& position, const glm::vec2& size)
{
    TActor* obj = new TActor(position.x, position.y, size.x, size.y);
    this->sceneGraph->addNode<TActor>(obj);
    return obj;
}

