#ifndef SCENE_SERIALIZER_H
#define SCENE_SERIALIZER_H

#include "Scene/Scene.h"
#include "json/json.hpp"
#include "glm/glm.hpp"
#include <string>
#include "Actor.h"
#include "TypeName.hpp"
#include "GameEngineAPI/ConsoleApi.h"
#include <iostream>
#include <vector>

namespace GameEngine
{
    using Json = nlohmann::json;
    class SceneSerializer
    {
    public:
        SceneSerializer();
        static void serializeEntity(Actor& actor, Json& json);
        void serialize(const std::string& path);
        bool deserialize(const std::string& path);
    };

    Json toJson(const glm::vec3& other);
    Json toJson(const glm::vec4& other);
    glm::vec3 vectorToVec3(const std::vector<float>& vec);
    glm::vec4 vectorToVec4(const std::vector<float>& vec);
}

#endif