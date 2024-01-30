#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include "lua.hpp"
#include "sol/sol.hpp"

namespace GameEngine
{
    class ScriptEngine
    {
    public:
        ScriptEngine();
        void test();
    private:
        sol::state luaState;
    };
}

#endif