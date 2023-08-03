#include "Component/Component.h"

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
