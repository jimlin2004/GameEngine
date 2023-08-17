#include "Scene/SceneSerializer.h"

#include "Core/GELib.h"
#include "GameEngineAPI/GameEngineAPI.h"
#include "GameEngineAPI/ConsoleApi.h"
#include "Core/Assert.h"

GameEngine::SceneSerializer::SceneSerializer()
{
}

void GameEngine::SceneSerializer::serializeEntity(Actor &actor, Json& jsonArray)
{
    Json jsonObject;
    if (actor.hasComponent<IDComponent>())
        jsonObject["UUID"] = actor.getComponent<IDComponent>().uuid;
    if (actor.hasComponent<TagComponent>())
        jsonObject["TagName"] = actor.getComponent<TagComponent>().tagName;
    if (actor.hasComponent<TransformComponent>())
    {
        TransformComponent& transformComponent = actor.getComponent<TransformComponent>();
        jsonObject["Transform"]["Position"] = toJson(transformComponent.translation);
        jsonObject["Transform"]["Scale"] = toJson(transformComponent.scale);
        jsonObject["Transform"]["Rotation"] = toJson(transformComponent.rotation);
    }
    if (actor.hasComponent<MeshComponent>())
    {
        MeshComponent& meshComponent = actor.getComponent<MeshComponent>();
        jsonObject["Mesh"]["Color"] = toJson(meshComponent.color);
        if (meshComponent.texture != nullptr)
            jsonObject["Mesh"]["Texture"] = GameEngine::GEngine->textureManager->getTextureFileName(meshComponent.texture->getTextureID());
    }
    if (actor.hasComponent<CameraComponent>())
    {
        jsonObject["Camera"]["Primary"] = actor.getComponent<CameraComponent>().primary;
    }
    if (actor.hasComponent<Rigidbody2DComponent>())
    {
        Rigidbody2DComponent& rigidbody2DComponent = actor.getComponent<Rigidbody2DComponent>();

        jsonObject["Rigidbody2D"]["BodyType"] = toJson(rigidbody2DComponent.type);
        jsonObject["Rigidbody2D"]["FixedRotation"] = rigidbody2DComponent.fixedRotation;
    }
    if (actor.hasComponent<BoxCollider2DComponent>())
    {
        BoxCollider2DComponent& boxCollider2DComponent = actor.getComponent<BoxCollider2DComponent>();

        jsonObject["BoxCollider2D"]["Offset"] = toJson(boxCollider2DComponent.offset);
        jsonObject["BoxCollider2D"]["Size"]   = toJson(boxCollider2DComponent.size);
        jsonObject["BoxCollider2D"]["Density"]  = boxCollider2DComponent.density;
        jsonObject["BoxCollider2D"]["Friction"] = boxCollider2DComponent.friction;
        jsonObject["BoxCollider2D"]["Restitution"] = boxCollider2DComponent.restitution;
        jsonObject["BoxCollider2D"]["RestitutionThreshold"] = boxCollider2DComponent.restitutionThreshold;
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
    if (GameEngine::globalScene != nullptr)
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
        if (jsonActor.contains("UUID"))
        {
            actor->addComponent<IDComponent>(jsonActor["UUID"].get<GameEngine::UUID>());
        }
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
            GameEngine::Texture* texture = nullptr;
            if (jsonActor["Mesh"].contains("Texture"))
            {
                std::string absoluteFilePath = GameEngine::GEngine->getWorkingDirname() + "/assets/texture" + jsonActor["Mesh"]["Texture"].get<std::string>();
                texture->load(absoluteFilePath.c_str(), GL_NEAREST);
            }
                
            actor->addComponent<MeshComponent>(color);
        }
        if (jsonActor.contains("Camera"))
        {
            actor->addComponent<GameEngine::CameraComponent>(jsonActor["Camera"]["Primary"].get<bool>());
        }
        if (jsonActor.contains("Rigidbody2D"))
        {
            GameEngine::Rigidbody2DComponent rigidbody2DComponent;
            rigidbody2DComponent.type = GameEngine::Rigidbody2DComponent::stringToBodyType(jsonActor["Rigidbody2D"]["BodyType"].get<std::string>());
            rigidbody2DComponent.fixedRotation = jsonActor["Rigidbody2D"]["FixedRotation"].get<bool>();
            actor->addComponent<GameEngine::Rigidbody2DComponent>(rigidbody2DComponent);
        }
        if (jsonActor.contains("BoxCollider2D"))
        {
            GameEngine::BoxCollider2DComponent boxCollider2DComponent;
            boxCollider2DComponent.offset = GameEngine::vectorToVec2(jsonActor["BoxCollider2D"]["Offset"].get<std::vector<float>>());
            boxCollider2DComponent.size   = GameEngine::vectorToVec2(jsonActor["BoxCollider2D"]["Size"].get<std::vector<float>>());
            boxCollider2DComponent.density     = jsonActor["BoxCollider2D"]["Density"].get<float>();
            boxCollider2DComponent.friction    = jsonActor["BoxCollider2D"]["Friction"].get<float>();
            boxCollider2DComponent.restitution = jsonActor["BoxCollider2D"]["Restitution"].get<float>();
            boxCollider2DComponent.restitutionThreshold = jsonActor["BoxCollider2D"]["RestitutionThreshold"].get<float>();
            actor->addComponent<GameEngine::BoxCollider2DComponent>(boxCollider2DComponent);
        }
    }
    return true;
}

bool GameEngine::SceneSerializer::deserialize(const std::string &path, Scene *scenePtr)
{
    if (scenePtr != nullptr)
        delete scenePtr;
    scenePtr = new Scene();
    GameEngine::Actor::bindScene(scenePtr);

    Json json;
    std::ifstream input(path);
    input >> json;
    Json jsonActors = json["Actors"];
    for (Json jsonActor: jsonActors)
    {
        Actor* actor = scenePtr->spawnActor<Actor>();
        if (jsonActor.contains("UUID"))
        {
            actor->addComponent<IDComponent>(jsonActor["UUID"].get<GameEngine::UUID>());
        }
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
            GameEngine::Texture* texture = nullptr;
            if (jsonActor["Mesh"].contains("Texture"))
            {
                std::string absoluteFilePath = GameEngine::GEngine->getWorkingDirname() + "/assets/texture" + jsonActor["Mesh"]["Texture"].get<std::string>();
                texture->load(absoluteFilePath.c_str(), GL_NEAREST);
            }
                
            actor->addComponent<MeshComponent>(color);
        }
        if (jsonActor.contains("Camera"))
        {
            actor->addComponent<GameEngine::CameraComponent>(jsonActor["Camera"]["Primary"].get<bool>());
        }
        if (jsonActor.contains("Rigidbody2D"))
        {
            GameEngine::Rigidbody2DComponent rigidbody2DComponent;
            rigidbody2DComponent.type = GameEngine::Rigidbody2DComponent::stringToBodyType(jsonActor["Rigidbody2D"]["BodyType"].get<std::string>());
            rigidbody2DComponent.fixedRotation = jsonActor["Rigidbody2D"]["FixedRotation"].get<bool>();
            actor->addComponent<GameEngine::Rigidbody2DComponent>(rigidbody2DComponent);
        }
        if (jsonActor.contains("BoxCollider2D"))
        {
            GameEngine::BoxCollider2DComponent boxCollider2DComponent;
            boxCollider2DComponent.offset = GameEngine::vectorToVec2(jsonActor["BoxCollider2D"]["Offset"].get<std::vector<float>>());
            boxCollider2DComponent.size   = GameEngine::vectorToVec2(jsonActor["BoxCollider2D"]["Size"].get<std::vector<float>>());
            boxCollider2DComponent.density     = jsonActor["BoxCollider2D"]["Density"].get<float>();
            boxCollider2DComponent.friction    = jsonActor["BoxCollider2D"]["Friction"].get<float>();
            boxCollider2DComponent.restitution = jsonActor["BoxCollider2D"]["Restitution"].get<float>();
            boxCollider2DComponent.restitutionThreshold = jsonActor["BoxCollider2D"]["RestitutionThreshold"].get<float>();
            actor->addComponent<GameEngine::BoxCollider2DComponent>(boxCollider2DComponent);
        }
    }
    return true;
}

GameEngine::Json GameEngine::toJson(const glm::vec2 &other)
{
    Json node = Json::array();
    node.push_back(other.x);
    node.push_back(other.y);
    return node;
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

GameEngine::Json GameEngine::toJson(const GameEngine::Rigidbody2DComponent::BodyType bodyType)
{
    Json node = GameEngine::Rigidbody2DComponent::bodyTypeToString(bodyType);
    return node;
}