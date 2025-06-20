#include "SDLFileParser.h"

#include <string>
#include <vector>
#include "GameEngineAPI/ConsoleApi.h"
#include "Actor/Actor.h"
#include "Scene/Scene.h"
#include "Component/Component.h"
#include "glm/glm.hpp"
#include "Core/GELib.h"

uint32_t GameEngineEditor::SDLFileParser::parseFile(const std::filesystem::path& filePath, const GameEngine::MousePosition &mousePosition, GameEngine::Scene* scene)
{
    std::string extension = filePath.extension().u8string();
    if (extension == ".asset")
    {
        return SDLFileParser::parseAssetFile(filePath, mousePosition, scene);
    }
    else
    {
        // unknow file type
        assert(false);
        throw std::runtime_error("Unknow file type");
    }
    return false;
}

uint32_t GameEngineEditor::SDLFileParser::parseAssetFile(const std::filesystem::path& filePath, const GameEngine::MousePosition &mousePosition, GameEngine::Scene* scene)
{
    Json json;
    std::ifstream input(filePath.u8string());
    input >> json;
    GameEngine::Actor* actor = scene->spawnActor<GameEngine::Actor>();
    if (json.contains("TagName"))
    {
        auto typeName_str_view = TYPE_NAME_BY_TYPE(GameEngine::Actor);
        std::string typeName = {typeName_str_view.begin(), typeName_str_view.end()};
        actor->addComponent<GameEngine::TagComponent>(json["TagName"].get<std::string>(), typeName);
    }
    if (json.contains("Transform"))
    {
        glm::vec3 position = {mousePosition.x, mousePosition.y, 1.0f};
        glm::vec3 scale = GameEngine::vectorToVec3(json["Transform"]["Scale"].get<std::vector<float>>());
        glm::vec3 rotation = GameEngine::vectorToVec3(json["Transform"]["Rotation"].get<std::vector<float>>());
        actor->addComponent<GameEngine::TransformComponent>(position, scale, rotation);
    }
    if (json.contains("Mesh"))
    {
        glm::vec4 color = GameEngine::vectorToVec4(json["Mesh"]["Color"]);
        actor->addComponent<GameEngine::MeshComponent>(color);
    }
    return actor->getID();
}