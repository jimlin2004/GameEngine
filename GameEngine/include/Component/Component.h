#ifndef GE_COMPONENT_H
#define GE_COMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Actor/Actor.h"
#include "Opengl/Texture.h"
#include <string>
#include "Core/UUID.h"
#include "Core/Camera.h"

namespace GameEngine
{
    struct IDComponent
    {
        UUID uuid;

        IDComponent() = default;
        IDComponent(const UUID& otherUUID);
        IDComponent(const IDComponent&) = default;
    };

    struct TagComponent
    {
        std::string tagName;
        std::string typeName;
        TagComponent();
        TagComponent(const TagComponent& other);
        TagComponent(const std::string& tagName, const std::string& typeName);
    };

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
        glm::vec4 color;
        Texture* texture;

        MeshComponent();
        MeshComponent(const MeshComponent& other);
        MeshComponent(const glm::vec4& color, GameEngine::Texture* texture = nullptr);
    };

    struct CameraComponent
    {
        Camera camera;
        bool primary;

        CameraComponent(bool isPrimary = false);
        CameraComponent(const CameraComponent& other);
        CameraComponent(const Camera& camera);
    };

    struct ScriptComponent
    {
        GameEngine::Character* instance;

        GameEngine::Character* (*instantiateScript)();
        void (*destroyScript)(ScriptComponent*);

        template<class T>
        void bind()
        {
            this->instantiateScript = []() {
                return static_cast<GameEngine::Character*>(new T());
            };
            this->destroyScript = [](ScriptComponent* scriptComponent) {
                delete (T*)scriptComponent->instance;
                scriptComponent->instance = nullptr;
            };
        }
    };
}


#endif