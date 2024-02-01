#include "Script/ScriptInstance.h"

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
    this->luaTable["update"](this->luaTable, deltaTime);
}
