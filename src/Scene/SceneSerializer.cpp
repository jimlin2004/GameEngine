#include "Scene/SceneSerializer.h"

GameEngine::SceneSerializer::SceneSerializer()
{
}

void GameEngine::SceneSerializer::serializeEntity(Actor &actor, Json& jsonArray)
{
    Json jsonObject;
    if (actor.hasComponent<TagComponent>())
        jsonObject["TagName"] = actor.getComponent<TagComponent>().tagName;
    if (actor.hasComponent<TransformComponent>())
    {
        TransformComponent transformComponent = actor.getComponent<TransformComponent>();
        jsonObject["Transform"]["Position"] = toJson(transformComponent.translation);
        jsonObject["Transform"]["Scale"] = toJson(transformComponent.scale);
        jsonObject["Transform"]["Rotation"] = toJson(transformComponent.rotation);
    }
    jsonArray.push_back(jsonObject);
}

void GameEngine::SceneSerializer::serialize(const std::string& path)
{
    Json jsonArray = Json::array();
    GameEngine::globalScene->registry.each([&jsonArray](auto entityID){
        GameEngine::Actor actor = {entityID};
        GameEngine::SceneSerializer::serializeEntity(actor, jsonArray);
    });
    std::ofstream output(path);
    output << jsonArray.dump(4);
}

bool GameEngine::SceneSerializer::deserialize(const std::string& path)
{
    // GameEngine::globalScene->registry.clear();
    // Json json = Json::parse(path);
    std::ifstream input(path);
    // std::cout << json.dump(4);
    return true;
}
GameEngine::Json GameEngine::toJson(const glm::vec3 &other)
{
    Json node = Json::array();
    node.push_back(other.x);
    node.push_back(other.y);
    node.push_back(other.z);
    return node;
}
