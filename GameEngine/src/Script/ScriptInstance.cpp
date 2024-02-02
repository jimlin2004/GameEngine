#include "Script/ScriptInstance.h"
#include "sol/sol.hpp"

GameEngine::ScriptInstance::ScriptInstance()
    : luaTable(sol::lua_nil)
{
}

void GameEngine::ScriptInstance::invokeConstructor()
{
    this->luaTable["new"](this->luaTable);
}

void GameEngine::ScriptInstance::begin()
{
    this->luaTable["begin"](this->luaTable);
}

void GameEngine::ScriptInstance::update(float deltaTime)
{
    try
    {
        this->luaTable["update"](this->luaTable, deltaTime);
    }
    catch(const sol::error& e)
    {
        std::cerr << e.what() << '\n';
    }
}
