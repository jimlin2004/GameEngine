#include "Script/ScriptEngine.h"

#include "Script/ScriptRegister.h"
#include "Script/ScriptInstance.h"

GameEngine::ScriptEngine::ScriptEngine()
    : luaState({})
{
    this->luaState.open_libraries(sol::lib::base);
    this->luaState.require_file("Input", "D:/code/cpp/gameEngine/GameEngine/ScriptCore/Input.lua");
    this->luaState.require_file("KeyCode", "D:/code/cpp/gameEngine/GameEngine/ScriptCore/KeyCode.lua");
    GameEngine::ScriptRegister::registerClass(this->luaState);
    GameEngine::ScriptRegister::registerFunctions(this->luaState);
}

void GameEngine::ScriptEngine::load(ScriptInstance& scriptInstance, const std::string& scriptPath)
{
    scriptInstance.luaTable = this->luaState.script_file("D:/code/cpp/gameEngine/luaTest/Test.lua");
}