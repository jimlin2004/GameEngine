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
    if (actor.hasComponent<MeshComponent>())
    {
        MeshComponent meshComponent = actor.getComponent<MeshComponent>();
        jsonObject["Mesh"]["Color"] = toJson(meshComponent.color);
    }
    jsonArray.push_back(jsonObject);
}

void GameEngine::SceneSerializer::serialize(const std::string& path)
{
    Json jsonRoot;
    Json jsonArray = Json::array();
    GameEngine::globalScene->registry.each([&jsonArray](auto entityID){
        GameEngine::Actor actor = {entityID};
        GameEngine::SceneSerializer::serializeEntity(actor, jsonArray);
    });
    jsonRoot["Actors"] = jsonArray;
    std::ofstream output(path);
    output << jsonRoot.dump(4);
}

bool GameEngine::SceneSerializer::deserialize(const std::string& path)
{
    delete GameEngine::globalScene;
    GameEngine::globalScene = new Scene();
    GameEngine::Actor::bindScene(GameEngine::globalScene);

    Json json;
    std::ifstream input(path);
    input >> json;
    Json jsonActors = json["Actors"];
    for (Json jsonActor: jsonActors)
    {
        Actor* actor = GameEngine::globalScene->spawnActor<Actor>();
        if (jsonActor.contains("TagName"))
        {
            auto typeName_str_view = TYPE_NAME_BY_TYPE(Actor);
            std::string typeName = {typeName_str_view.begin(), typeName_str_view.end()};
            actor->addComponent<TagComponent>(jsonActor["TagName"].get<std::string>(), typeName);
        }
        if (jsonActor.contains("Transform"))
        {
            glm::vec3 position = GameEngine::vectorToVec3(jsonActor["Transform"]["Position"].get<std::vector<float>>());
            glm::vec3 scale = GameEngine::vectorToVec3(jsonActor["Transform"]["Scale"].get<std::vector<float>>());
            glm::vec3 rotation = GameEngine::vectorToVec3(jsonActor["Transform"]["Rotation"].get<std::vector<float>>());
            actor->addComponent<TransformComponent>(position, scale, rotation);
        }
        if (jsonActor.contains("Mesh"))
        {
            glm::vec4 color = GameEngine::vectorToVec4(jsonActor["Mesh"]["Color"]);
            actor->addComponent<MeshComponent>(color);
        }
    }
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

GameEngine::Json GameEngine::toJson(const glm::vec4 &other)
{
    Json node = Json::array();
    node.push_back(other.r);
    node.push_back(other.g);
    node.push_back(other.b);
    node.push_back(other.a);
    return node;
}

glm::vec3 GameEngine::vectorToVec3(const std::vector<float> &vec)
{
    return {vec[0], vec[1], vec[2]};
}

glm::vec4 GameEngine::vectorToVec4(const std::vector<float> &vec)
{
    return {vec[0], vec[1], vec[2], vec[3]};
}