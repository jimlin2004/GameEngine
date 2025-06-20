#include "Script/ScriptInstance.h"
#include "sol/sol.hpp"

GameEngine::Script::ScriptInstance::ScriptInstance()
    : luaTable(sol::lua_nil)
{
}

void GameEngine::Script::ScriptInstance::invokeConstructor()
{
    try
    {
        this->luaTable["new"](this->luaTable);
    }
    catch(const sol::error& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void GameEngine::Script::ScriptInstance::begin()
{
    this->luaTable["begin"](this->luaTable);
}

void GameEngine::Script::ScriptInstance::update(float deltaTime)
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
