#ifndef GE_COMPONENT_H
#define GE_COMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>

namespace GameEngine
{
    struct TransformComponent
    {
        glm::vec3 translation = {0.0f, 0.0f, 0.0f};
        glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
        glm::vec3 scale = {1.0f, 1.0f, 1.0f};

        TransformComponent() = default;
        TransformComponent(const TransformComponent& other);
        TransformComponent(const glm::vec3& translation, const glm::vec3& scale, const glm::vec3& rotation);
        glm::mat4 getTransform() const;
    };

    struct MeshComponent
    {
        glm::vec4 color {1.0, 1.0, 1.0, 1.0};

        MeshComponent() = default;
        MeshComponent(const MeshComponent& other);
        MeshComponent(const glm::vec4& color);
    };

    struct TagComponent
    {
        std::string tagName;
        std::string typeName;
        TagComponent();
        TagComponent(const TagComponent& other);
        TagComponent(const std::string& tagName, const std::string& typeName);
    };
}


#endif