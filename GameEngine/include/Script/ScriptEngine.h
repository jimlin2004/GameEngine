#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include <string>
#include "entt.hpp"
#include "Script/ScriptEngineMacro.h"

namespace GameEngine
{
    class Actor;
    class Scene;
    class ScriptEngine
    {
    public:
        //初始化Script engine
        static void init(const std::string& dllPath);

        static Actor* createActor(const std::string& actorType, entt::entity entityID, Scene* scenePtr);
    };

    GENGINE_API void DLLtest();
}

#endif