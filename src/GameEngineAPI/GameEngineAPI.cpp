#include "../include/GameEngineApi/GameEngineApi.h"

GameEngine::GameEngineAPI::GameEngineAPI()
{
    this->gameEventManager = new GameEventManager();
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
}
