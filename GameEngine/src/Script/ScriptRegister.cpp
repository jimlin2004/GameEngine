#include "Script/ScriptRegister.h"

#include "Core/GameEngineCore.h"

//不清楚為什麼不能直接用GameEngine::Input::isKeyPressed引入Lua，改用此函式包裝
static inline bool input_isKeyPressed(uint32_t keyCode)
{
    return GameEngine::Input::isKeyPressed((GameEngine::KeyCode)keyCode);
}

void GameEngine::ScriptRegister::registerClass(sol::state &luaState)
{
}

void GameEngine::ScriptRegister::registerFunctions(sol::state& luaState)
{
    luaState.set_function("cpp_Input_isKeyPressed", &input_isKeyPressed);
    luaState.set_function("cpp_Input_getMouseX", sol::resolve<int(void)>(GameEngine::Input::getMouseX));
    luaState.set_function("cpp_Input_getMouseY", sol::resolve<int(void)>(GameEngine::Input::getMouseY));
}

void GameEngine::ScriptRegister::registerComponents()
{
}
