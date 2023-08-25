#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include <string>
#include <vector>
#include "entt.hpp"
#include "Script/ScriptEngineMacro.h"

namespace GameEngine
{
    class Character;
    class Scene;
    
    class ScriptEngine
    {
    public:
        // 初始化Script engine
        static void init(const std::string& dllPath);
        // 關閉ScriptEngine，free dll
        static void stop();
        // 重新load dll
        static void reload(const std::string& dllPath);
        // 調用classMap呼叫dll中的scriptable character建構子
        static Character* createActor(const std::string& actorType, entt::entity entityID, Scene* scenePtr);
        // 得到所有class name
        static std::vector<std::string> getAllClassName();
    };
}

#endif