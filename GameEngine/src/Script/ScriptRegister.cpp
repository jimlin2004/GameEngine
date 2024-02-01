#include "Script/ScriptRegister.h"

#include "Core/GameEngineCore.h"
#include "Scene/Scene.h"

struct ScriptRegisterData
{
    uint32_t targetEntityID;
};

static ScriptRegisterData scriptRegisterData;

//only use in GameEngine
static inline uint32_t getScriptEngineTargetEntityID()
{
    return scriptRegisterData.targetEntityID;
}

//不清楚為什麼不能直接用GameEngine::Input::isKeyPressed引入Lua，改用此函式包裝
static inline bool input_isKeyPressed(uint32_t keyCode)
{
    return GameEngine::Input::isKeyPressed((GameEngine::KeyCode)keyCode);
}

void GameEngine::ScriptRegister::registerClass(sol::state &luaState, GameEngine::Scene* scene)
{
}

void GameEngine::ScriptRegister::registerFunctions(sol::state& luaState, GameEngine::Scene* scene)
{
    luaState.set_function("cpp_Input_isKeyPressed", &input_isKeyPressed);
    luaState.set_function("cpp_Input_getMouseX", sol::resolve<int(void)>(GameEngine::Input::getMouseX));
    luaState.set_function("cpp_Input_getMouseY", sol::resolve<int(void)>(GameEngine::Input::getMouseY));
    luaState.set_function("cpp_getScriptEngineTargetEntityID", &getScriptEngineTargetEntityID);
}

void GameEngine::ScriptRegister::registerComponents()
{
}


void GameEngine::ScriptRegister::setTargetEntityID(uint32_t id)
{
    scriptRegisterData.targetEntityID = id;
}
