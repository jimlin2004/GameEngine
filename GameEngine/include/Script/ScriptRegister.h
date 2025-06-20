#ifndef SCRIPT_REGISTER_H
#define SCRIPT_REGISTER_H

#include "lua.hpp"
#include "sol/sol.hpp"

namespace GameEngine
{
    class Scene;

    namespace Script
    {
        class ScriptRegister
        {
        public:
            static void registerClass(sol::state& luaState, Scene* scene);
            static void registerFunctions(sol::state& luaState, Scene* scene);
            static void registerComponents();

            static void setTargetEntityID(uint32_t id);
        };
    }
}

#endif