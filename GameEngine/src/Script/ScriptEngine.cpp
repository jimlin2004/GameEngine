#include "Script/ScriptEngine.h"

#include "Scene/Scene.h"
#include "Script/ScriptRegister.h"
#include "Script/ScriptInstance.h"

GameEngine::ScriptEngine::ScriptEngine()
    : luaState({})
{
}

void GameEngine::ScriptEngine::init(GameEngine::Scene* scene)
{
    this->luaState.open_libraries(sol::lib::base);
    this->luaState.require_file("Input", "D:/code/cpp/gameEngine/GameEngine/ScriptCore/Input.lua");
    this->luaState.require_file("KeyCode", "D:/code/cpp/gameEngine/GameEngine/ScriptCore/KeyCode.lua");
    this->luaState.require_file("Actor", "D:/code/cpp/gameEngine/GameEngine/ScriptCore/Actor.lua");
    GameEngine::ScriptRegister::registerClass(this->luaState, scene);
    GameEngine::ScriptRegister::registerFunctions(this->luaState, scene);
}

void GameEngine::ScriptEngine::load(ScriptInstance& scriptInstance, const std::string& scriptPath)
{
    scriptInstance.luaTable = this->luaState.script_file(scriptPath);
}

void GameEngine::ScriptEngine::close()
{
}

void GameEngine::ScriptEngine::setTargetEntityID(uint32_t id)
{

}