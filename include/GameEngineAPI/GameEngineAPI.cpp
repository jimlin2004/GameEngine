#include "GameEngineAPI.h"

GameEngine::GameEngineAPI::GameEngineAPI()
{
    this->gameEventManager = new GameEventManager();
}

void GameEngine::GameEngineAPI::callKeyEvent(int key)
{
    this->gameEventManager->callKeyEvent(key);
}

namespace GameEngine
{
    //GEgine的實現
    GameEngineAPI* GEngine = new GameEngineAPI();
}
