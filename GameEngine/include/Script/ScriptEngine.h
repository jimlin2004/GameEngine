#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include "lua.hpp"
#include "sol/sol.hpp"

namespace GameEngine
{
    class ScriptInstance;
    class Scene;

    class ScriptEngine
    {
    public:
        ScriptEngine();
        void init(Scene* scene);
        void load(ScriptInstance& scriptInstance, const std::string& scriptPath);
        void close();

        void setTargetEntityID(uint32_t id);
    private:
        sol::state luaState;
    };
}

#endif