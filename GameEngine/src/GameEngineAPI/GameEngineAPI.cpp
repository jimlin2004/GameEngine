#include "GameEngineApi/GameEngineApi.h"

#include <filesystem>

GameEngine::GameEngineAPI::GameEngineAPI()
    : shaderManager(new GameEngine::ShaderManager())
    , textureManager(new GameEngine::TextureManager())
    , editorSceneBeginFunc(nullptr)
    , workingDirname(std::filesystem::current_path().u8string())
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

void GameEngine::GameEngineAPI::_setWindowSize(float _w, float _h)
{
    this->_windowWidth = _w;
    this->_windowHeight = _h;
}

void GameEngine::GameEngineAPI::setWorkingDirname(const std::string &path)
{
    this->workingDirname = path;
}

namespace GameEngine
{
    //GEgine的實現
    GameEngineAPI* GEngine = new GameEngineAPI();
    // glm::mat4 PROJECTION_MATRIX = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    //在GameBase會修改(隨GameBase->screenWidth、GameBase->height改變)
    CameraController* cameraController = new CameraController(new Camera());
}
