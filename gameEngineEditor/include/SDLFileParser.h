#ifndef SDL_FILE_PARSER
#define SDL_FILE_PARSER

#include <string>
#include <filesystem>
#include "json/json.hpp"
#include <exception>
#include <fstream>
#include "entt.hpp"
#include "Event/Input.h"
#include "Scene/Scene.h"

namespace GameEngineEditor
{
    using Json = nlohmann::json;

    class SDLFileParser
    {
    public:
        static uint32_t parseFile(const std::filesystem::path& filePath, const GameEngine::MousePosition& mousePosition, GameEngine::Scene* scene);
    private:
        static uint32_t parseAssetFile(const std::filesystem::path& filePath, const GameEngine::MousePosition& mousePosition, GameEngine::Scene* scene);
    };
}


#endif