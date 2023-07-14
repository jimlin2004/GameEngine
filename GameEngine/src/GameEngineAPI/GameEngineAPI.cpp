#include "GameEngineApi/GameEngineApi.h"

GameEngine::GameEngineAPI::GameEngineAPI()
    : shaderManager(new GameEngine::ShaderManager())
    , editorSceneBeginFunc(nullptr)
{

}
GameEngine::GameEngineAPI::~GameEngineAPI()
{
    delete this->shaderManager;
}

void GameEngine::GameEngineAPI::setEditorSceneFunc(std::function<void()> func)
{
    this->editorSceneBeginFunc = func;
}

// void GameEngine::GameEngineAPI::callKeyEvent(int key)
// {
//     this->gameEventManager->callKeyEvent(key);
//     return;
// }

// void GameEngine::GameEngineAPI::addKeyEvent(int key, std::function<void()> func)
// {
//     this->gameEventManager->bindKeyEvent(key, func);
//     return;
// }

void GameEngine::GameEngineAPI::_setWindowSize(float _w, float _h)
{
    this->_windowWidth = _w;
    this->_windowHeight = _h;
}

namespace GameEngine
{
    //GEgine的實現
    GameEngineAPI* GEngine = new GameEngineAPI();
    // glm::mat4 PROJECTION_MATRIX = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    //在GameBase會修改(隨GameBase->screenWidth、GameBase->height改變)
    CameraController* cameraController = new CameraController(new Camera());
}
