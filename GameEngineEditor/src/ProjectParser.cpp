#include "ProjectParser.h"

#include <filesystem>
#include <fstream>

GameEngineEditor::ProjectParser::ProjectParser()
{
}

void GameEngineEditor::ProjectParser::load(const std::string& projectPath)
{
    Json json;
    std::ifstream input(projectPath);
    input >> json;

    std::filesystem::path path(projectPath);

    this->projectPath = projectPath;
    this->projectDirname = path.parent_path().string();
    this->projectName = json["Project"]["Name"].get<std::string>();
}
