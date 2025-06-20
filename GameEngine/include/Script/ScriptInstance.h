#ifndef SCRIPT_INSTANCE_H
#define SCRIPT_INSTANCE_H

#include "lua.hpp"
#include "sol/sol.hpp"
#include "Script/ScriptEngine.h"

namespace GameEngine
{
    namespace Script
    {
        class ScriptInstance
        {
        public:
            ScriptInstance();
            void invokeConstructor();
            void begin();
            void update(float deltaTime);
        private:
            sol::table luaTable;
        
            friend ScriptEngine;
        };
    }
}

#endif