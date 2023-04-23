#include "Scene.h"

GameEngine::Scene::Scene()
{
    this->sceneGraph = new GameEngine::SceneGraph();
}

GameEngine::Scene::~Scene()
{
    delete this->sceneGraph;
}

void GameEngine::Scene::unpdateScene()
{
}
