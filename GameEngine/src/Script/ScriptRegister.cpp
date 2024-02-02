#include "Script/ScriptRegister.h"

#include "Core/GameEngineCore.h"
#include "Scene/Scene.h"
#include "glm/glm.hpp"

static glm::vec2 tempVec(0, 0);

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
    //Vec2
    luaState.new_usertype<glm::vec2>(
        "cpp_Vec2", 
        sol::call_constructor,
        sol::constructors<glm::vec2(float), glm::vec2(float, float)>(),
        "x", &glm::vec2::x,
        "y", &glm::vec2::y
    );

    //TransformComponent
}

void GameEngine::ScriptRegister::registerFunctions(sol::state& luaState, GameEngine::Scene* scene)
{
    luaState.set_function("cpp_Input_isKeyPressed", &input_isKeyPressed);
    luaState.set_function("cpp_Input_getMouseX", sol::resolve<int(void)>(GameEngine::Input::getMouseX));
    luaState.set_function("cpp_Input_getMouseY", sol::resolve<int(void)>(GameEngine::Input::getMouseY));
    luaState.set_function("cpp_getScriptEngineTargetEntityID", &getScriptEngineTargetEntityID);

    luaState.set_function("cpp_test", [&](){
        tempVec.x += 1;
    });
    luaState.set_function("cpp_getTemp", [&](sol::this_state s) {
        return sol::make_reference(s, std::ref(tempVec));
    });
}

void GameEngine::ScriptRegister::registerComponents()
{
}


void GameEngine::ScriptRegister::setTargetEntityID(uint32_t id)
{
    scriptRegisterData.targetEntityID = id;
}
