#ifndef GE_COMPONENT_H
#define GE_COMPONENT_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Actor/Actor.h"
#include <string>
#include "Core/UUID.h"
#include "Core/Camera.h"

namespace GameEngine
{
    class Texture;
    namespace Script
    {
        class ScriptInstance;
    }

    enum class GameEngineComponentType
    {
        Null = 0,
        IDComponent,
        TagComponent,
        TransformComponent,
        MeshComponent,
        CameraComponent,
        ScriptComponent,
        Rigidbody2DComponent,
        BoxCollider2DComponent
    };

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
        ScriptComponent();
        ScriptComponent(const ScriptComponent& other);
        GameEngine::Script::ScriptInstance* instance;
        std::string scriptPath;
    };

    //physics

    struct Rigidbody2DComponent
    {
        enum class BodyType {
            Static = 0, Dynamic, Kinematic
        };
        BodyType type = BodyType::Static;
        bool fixedRotation = false;

        //storage for runtime(b2Body*)
        void* runtimeBody = nullptr;

        Rigidbody2DComponent() = default;
        Rigidbody2DComponent(const Rigidbody2DComponent& other) = default;
    
        static BodyType stringToBodyType(const std::string& str);
        static std::string bodyTypeToString(BodyType bodyType);
    };

    struct BoxCollider2DComponent
    {
        glm::vec2 offset = {0.0f, 0.0f};
        glm::vec2 size   = {0.5f, 0.5f};

        //密度
        float density  = 1.0f;
        //摩擦力
        float friction = 0.0f;
        //恢復係數
        float restitution = 0.0f;
        //恢復係數閾值
        float restitutionThreshold = 0.5f;

        void* runtimeFixture = nullptr;

        BoxCollider2DComponent() = default;
        BoxCollider2DComponent(const BoxCollider2DComponent& other) = default;
    };

    template <typename ...Component>
    struct ComponentGroup
    {
    };

    //無IDComponent
    using AllCompnents = ComponentGroup<TagComponent,
        TransformComponent, MeshComponent, CameraComponent,
        ScriptComponent, Rigidbody2DComponent, BoxCollider2DComponent>;
}


#endif