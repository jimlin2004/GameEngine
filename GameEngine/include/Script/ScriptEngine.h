#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include <string>
#include "entt.hpp"
#include "Script/ScriptEngineMacro.h"

namespace GameEngine
{
    class Character;
    class Scene;
    class ScriptEngine
    {
    public:
        //初始化Script engine
        static void init(const std::string& dllPath);

        static Character* createActor(const std::string& actorType, entt::entity entityID, Scene* scenePtr);
    };
}

#endif