#include "runtime/SDL/SDLFileParser.h"

#include "GameEngineAPI/ConsoleApi.h"

void GameEngineEditor::SDLFileParser::parseFile(const std::filesystem::path& filePath, const GameEngine::MousePosition &mousePosition)
{
    std::string extension = filePath.extension().u8string();
    if (extension == ".asset")
    {
        SDLFileParser::parseAssetFile(filePath, mousePosition);
    }
    else
    {
        // unknow file type
        assert(false);
        throw std::runtime_error("Unknow file type");
    }
}
void GameEngineEditor::SDLFileParser::parseAssetFile(const std::filesystem::path& filePath, const GameEngine::MousePosition &mousePosition)
{
    Json json;
    std::ifstream input(filePath.u8string());
    input >> json;
    GameEngine::ConsoleApi::log() << json;
}