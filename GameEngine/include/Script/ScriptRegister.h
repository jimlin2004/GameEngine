#ifndef SCRIPT_REGISTER_H
#define SCRIPT_REGISTER_H

#include "lua.hpp"
#include "sol/sol.hpp"

namespace GameEngine
{
    class ScriptRegister
    {
    public:
        static void registerClass(sol::state& luaState);
        static void registerFunctions(sol::state& luaState);
        static void registerComponents();
    };
}

#endif