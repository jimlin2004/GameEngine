#include "Script/ScriptEngine.h"

GameEngine::ScriptEngine::ScriptEngine()
    : luaState({})
{
    this->luaState.open_libraries(sol::lib::base);
}

void GameEngine::ScriptEngine::test()
{
    this->luaState.script_file("D:/code/cpp/gameEngine/luaTest/Test.lua");
}