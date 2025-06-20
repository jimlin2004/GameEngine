#include "Script/ScriptEngine.h"

#include "Scene/Scene.h"
#include "Script/ScriptRegister.h"
#include "Script/ScriptInstance.h"

#include "GameEngineAPI/GameEngineAPI.h"
#include <filesystem>

GameEngine::Script::ScriptEngine::ScriptEngine()
    : luaState({})
{
}

void GameEngine::Script::ScriptEngine::init(GameEngine::Scene* scene)
{
    this->luaState.open_libraries(sol::lib::base,
                                sol::lib::package,
                                sol::lib::coroutine,
                                sol::lib::string,
                                sol::lib::os,
                                sol::lib::math,
                                sol::lib::table,
                                sol::lib::debug,
                                sol::lib::bit32,
                                sol::lib::io,
                                sol::lib::utf8);
    // this->luaState.require_file("Input", "D:/code/cpp/gameEngine/GameEngine/ScriptCore/Input.lua");
    // this->luaState.require_file("KeyCode", "D:/code/cpp/gameEngine/GameEngine/ScriptCore/KeyCode.lua");
    // this->luaState.require_file("Actor", "D:/code/cpp/gameEngine/GameEngine/ScriptCore/Actor.lua");
    // this->luaState.require_file("GameEngineDebugger", "D:/code/cpp/gameEngine/GameEngine/ScriptCore/GameEngineDebugger.lua");
    std::filesystem::path luaScriptCorePath(GameEngine::GEngine->getGameEnginePath());
    luaScriptCorePath /= "ScriptCore";
    this->luaState.require_file("Input", (luaScriptCorePath / "Input.lua").u8string());
    this->luaState.require_file("KeyCode", (luaScriptCorePath / "KeyCode.lua").u8string());
    this->luaState.require_file("Actor", (luaScriptCorePath / "Actor.lua").u8string());
    this->luaState.require_file("GameEngineDebugger", (luaScriptCorePath / "GameEngineDebugger.lua").u8string());
    GameEngine::Script::ScriptRegister::registerClass(this->luaState, scene);
    GameEngine::Script::ScriptRegister::registerFunctions(this->luaState, scene);
}

void GameEngine::Script::ScriptEngine::load(GameEngine::Script::ScriptInstance& scriptInstance, const std::string& scriptPath)
{
    try
    {
        sol::table luaClass = this->luaState.safe_script_file(scriptPath);
        scriptInstance.luaTable = luaClass["new"]();
    }
    catch(const sol::error& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void GameEngine::Script::ScriptEngine::close()
{
}

void GameEngine::Script::ScriptEngine::setTargetEntityID(uint32_t id)
{
    GameEngine::Script::ScriptRegister::setTargetEntityID(id);
}