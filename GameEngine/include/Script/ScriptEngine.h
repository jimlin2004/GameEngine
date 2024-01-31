#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include "lua.hpp"
#include "sol/sol.hpp"

namespace GameEngine
{
    class ScriptInstance;

    class ScriptEngine
    {
    public:
        ScriptEngine();
        void load(ScriptInstance& scriptInstance, const std::string& scriptPath);
    private:
        sol::state luaState;
    };
}

#endif