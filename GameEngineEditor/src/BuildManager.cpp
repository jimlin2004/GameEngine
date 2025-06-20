#include "BuildManager.h"

#include "GameEngineAPI/GameEngineAPI.h"

#include <filesystem>
#include <cstdlib>
#include <string>

bool GameEngineEditor::BuildManager::buildGame()
{
    std::filesystem::path pythonPath = std::filesystem::current_path() / ".." / ".." / "BuildSystem" / "Python/python.exe";

    std::filesystem::path scriptPath = std::filesystem::current_path() / ".." / ".." / "BuildSystem" / "build_game.py";

    std::string params = "--project_name " + GameEngine::GEngine->getProjectName()
                        + " --project_root " + GameEngine::GEngine->getProjectRootPath();

    std::string cmd = pythonPath.string() + ' ' + scriptPath.string() + ' ' + params;

    std::system(cmd.c_str());
    return false;
}