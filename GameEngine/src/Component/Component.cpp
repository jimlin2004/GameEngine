#include "Component/Component.h"

#include "Opengl/Texture.h"
#include "Core/Assert.h"

GameEngine::TransformComponent::TransformComponent(const TransformComponent &other)
    : translation(other.translation)
    , rotation(other.rotation)
    , scale(other.scale)
{
}

GameEngine::TransformComponent::TransformComponent(const glm::vec3& translation, const glm::vec3& scale, const glm::vec3& rotation)
    : translation(translation)
    , rotation(rotation)
    , scale(scale)
{
}

glm::mat4 GameEngine::TransformComponent::getTransform() const
{
    return glm::translate(glm::mat4(1.0f), translation)
        * glm::mat4_cast(glm::quat(rotation))
        * glm::scale(glm::mat4(1.0f), scale);
        // * glm::mat4_cast(glm::quat(glm::radians(rotation)))
}

GameEngine::MeshComponent::MeshComponent()
    : color({1.0f, 1.0f, 1.0f, 1.0f})
    , texture(nullptr) 
{
}

GameEngine::MeshComponent::MeshComponent(const MeshComponent &other)
    : color(other.color)
    , texture(other.texture) 
{
}

GameEngine::MeshComponent::MeshComponent(const glm::vec4 &color, GameEngine::Texture* texture)
    : color(color)
    , texture(texture)
{
}

GameEngine::TagComponent::TagComponent()
    : tagName("GameObject")
    , typeName("unknow")
{
}

GameEngine::TagComponent::TagComponent(const TagComponent &other)
    : tagName(other.tagName)
    , typeName(other.typeName)
{
}

GameEngine::TagComponent::TagComponent(const std::string &tagName, const std::string& typeName)
    : tagName(tagName)
    , typeName(typeName)
{
}

GameEngine::CameraComponent::CameraComponent(bool isPrimary)
    : primary(isPrimary)
{
}

GameEngine::CameraComponent::CameraComponent(const CameraComponent &other)
    : primary(other.primary)
{
}

GameEngine::CameraComponent::CameraComponent(const Camera &camera)
    : primary(false)
    , camera(camera)
{
}

GameEngine::IDComponent::IDComponent(const UUID &otherUUID)
    : uuid(otherUUID)
{
}

GameEngine::Rigidbody2DComponent::BodyType GameEngine::Rigidbody2DComponent::stringToBodyType(const std::string &str)
{
    if (str == "Static")
        return GameEngine::Rigidbody2DComponent::BodyType::Static;
    if (str == "Dynamic")
        return GameEngine::Rigidbody2DComponent::BodyType::Dynamic;
    if (str == "Kinematic")
        return GameEngine::Rigidbody2DComponent::BodyType::Kinematic;
    
    GAME_ENGINE_ASSERT(false, "Unknow rigidbody type");
    return GameEngine::Rigidbody2DComponent::BodyType::Static;
}
std::string GameEngine::Rigidbody2DComponent::bodyTypeToString(BodyType bodyType)
{
    switch (bodyType)
    {
    case GameEngine::Rigidbody2DComponent::BodyType::Static:
        return "Static";
    case GameEngine::Rigidbody2DComponent::BodyType::Dynamic:
        return "Dynamic";
    case GameEngine::Rigidbody2DComponent::BodyType::Kinematic:
        return "Kinematic";
    default:
        break;
    }

    GAME_ENGINE_ASSERT(false, "Unknow rigidbody type");
    return "Static";
}

GameEngine::ScriptComponent::ScriptComponent()
    : instance(nullptr)
    , className("None")
{
}

GameEngine::ScriptComponent::ScriptComponent(const GameEngine::ScriptComponent& other)
    : instance(other.instance)
    , className(other.className)
{
}

GameEngine::ScriptComponent::ScriptComponent(const std::string &newClassName)
    : instance(nullptr)
    , className(newClassName)
{
}
