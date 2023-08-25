#include "GameEngineApi/GameEngineApi.h"

#include "Opengl/ShaderManager.h"
#include "Opengl/TextureManager.h"
#include "Core/CameraController.h"

#include <filesystem>

GameEngine::GameEngineAPI::GameEngineAPI()
    : shaderManager(new GameEngine::ShaderManager())
    , textureManager(new GameEngine::TextureManager())
    , editorSceneBeginFunc(nullptr)
    , projectRootPath(std::filesystem::current_path().u8string())
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

void GameEngine::GameEngineAPI::setProjectRootPath(const std::string &path)
{
    this->projectRootPath = path;
}

void GameEngine::GameEngineAPI::setProjectName(const std::string &name)
{
    this->projectName = name;
}

namespace GameEngine
{
    //GEgine的實現
    GameEngineAPI* GEngine = new GameEngineAPI();
    // glm::mat4 PROJECTION_MATRIX = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    //在GameBase會修改(隨GameBase->screenWidth、GameBase->height改變)
    CameraController* cameraController = new CameraController(new Camera());
}
