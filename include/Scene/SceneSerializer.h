#ifndef SCENE_SERIALIZER_H
#define SCENE_SERIALIZER_H

#include "Scene/Scene.h"
#include "json/json.hpp"
#include "glm/glm.hpp"
#include <string>
#include "Actor.h"
#include "GameEngineAPI/ConsoleApi.h"
#include <iostream>

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
}

#endif