#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include <string>

namespace GameEngine
{
    class Actor;
    class ScriptEngine
    {
        //初始化Script engine
        static void init(const std::string& dllPath);

        static Actor* createActor(const std::string& actorType);
    };
}

#endif