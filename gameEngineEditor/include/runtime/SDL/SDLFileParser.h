#ifndef SDL_FILE_PARSER
#define SDL_FILE_PARSER

#include <string>
#include <filesystem>
#include <json/json.hpp>
#include <exception>
#include <fstream>
#include "Event/Input.h"

namespace GameEngineEditor
{
    using Json = nlohmann::json;

    class SDLFileParser
    {
    public:
        static void parseFile(const std::filesystem::path& filePath, const GameEngine::MousePosition& mousePosition);
    private:
        static void parseAssetFile(const std::filesystem::path& filePath, const GameEngine::MousePosition& mousePosition);
    };
}


#endif