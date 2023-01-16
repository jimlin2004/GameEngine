#include "../include/GameEngineApi/GameEngineApi.h"

GameEngine::GameEngineAPI::GameEngineAPI()
{
    this->shaderManager = new GameEngine::ShaderManager();
    this->gameEventManager = new GameEngine::GameEventManager();
}

void GameEngine::GameEngineAPI::callKeyEvent(int key)
{
    this->gameEventManager->callKeyEvent(key);
    return;
}

void GameEngine::GameEngineAPI::addKeyEvent(int key, std::function<void()> func)
{
    this->gameEventManager->bindKeyEvent(key, func);
    return;
}

namespace GameEngine
{
    //GEgine的實現
    GameEngineAPI* GEngine = new GameEngineAPI();
    //在GameBase會修改(隨GameBase->screenWidth、GameBase->height改變)
    glm::mat4 PROJECTION_MATRIX = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}
