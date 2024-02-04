#include "Script/ScriptRegister.h"

#include "Core/GameEngineCore.h"
#include "Scene/Scene.h"
#include "glm/glm.hpp"

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

static inline void test(std::string str)
{
    printf("%s\n", str.c_str());
}

void GameEngine::ScriptRegister::registerClass(sol::state &luaState, GameEngine::Scene* scene)
{
    //Vec2
    luaState.new_usertype<glm::vec2>(
        "Vec2", 
        sol::call_constructor,
        sol::constructors<glm::vec2(float), glm::vec2(float, float)>(),
        "x", &glm::vec2::x,
        "y", &glm::vec2::y,
        sol::meta_function::addition, sol::overload(
            [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1 + v2; },
            [](const glm::vec2& v1, float value) -> glm::vec2 { return v1 + value; },
            [](float value, const glm::vec2& v1) -> glm::vec2 { return v1 + value; }
        ),
        sol::meta_function::subtraction, sol::overload(
            [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1 - v2; },
            [](const glm::vec2& v1, float value) -> glm::vec2 { return v1 - value; },
            [](float value, const glm::vec2& v1) -> glm::vec2 { return v1 - value; }
        ),
        sol::meta_function::multiplication, sol::overload(
            [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1 * v2; },
            [](const glm::vec2& v1, float value) -> glm::vec2 { return v1 * value; },
            [](float value, const glm::vec2& v1) -> glm::vec2 { return v1 * value; }
        ),
        sol::meta_function::division, sol::overload(
            [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1 / v2; },
            [](const glm::vec2& v1, float value) -> glm::vec2 { return v1 / value; },
            [](float value, const glm::vec2& v1) -> glm::vec2 { return v1 / value; }
        )
    );

    //Vec3
    luaState.new_usertype<glm::vec3>(
        "Vec3", 
        sol::call_constructor,
        sol::constructors<glm::vec3(float), glm::vec3(float, float, float)>(),
        "x", &glm::vec3::x,
        "y", &glm::vec3::y,
        "z", &glm::vec3::z,
        sol::meta_function::addition, sol::overload(
            [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 + v2; },
            [](const glm::vec3& v1, float value) -> glm::vec3 { return v1 + value; },
            [](float value, const glm::vec3& v1) -> glm::vec3 { return v1 + value; }
        ),
        sol::meta_function::subtraction, sol::overload(
            [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 - v2; },
            [](const glm::vec3& v1, float value) -> glm::vec3 { return v1 - value; },
            [](float value, const glm::vec3& v1) -> glm::vec3 { return v1 - value; }
        ),
        sol::meta_function::multiplication, sol::overload(
            [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 * v2; },
            [](const glm::vec3& v1, float value) -> glm::vec3 { return v1 * value; },
            [](float value, const glm::vec3& v1) -> glm::vec3 { return v1 * value; }
        ),
        sol::meta_function::division, sol::overload(
            [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 / v2; },
            [](const glm::vec3& v1, float value) -> glm::vec3 { return v1 / value; },
            [](float value, const glm::vec3& v1) -> glm::vec3 { return v1 / value; }
        )
    );

    //Vec4
    luaState.new_usertype<glm::vec4>(
        "Vec4", 
        sol::call_constructor,
        sol::constructors<glm::vec4(float), glm::vec4(float, float, float, float)>(),
        "x", &glm::vec4::x,
        "y", &glm::vec4::y,
        "z", &glm::vec4::z,
        "w", &glm::vec4::w,
        sol::meta_function::addition, sol::overload(
            [](const glm::vec4& v1, const glm::vec4& v2) -> glm::vec4 { return v1 + v2; },
            [](const glm::vec4& v1, float value) -> glm::vec4 { return v1 + value; },
            [](float value, const glm::vec4& v1) -> glm::vec4 { return v1 + value; }
        ),
        sol::meta_function::subtraction, sol::overload(
            [](const glm::vec4& v1, const glm::vec4& v2) -> glm::vec4 { return v1 - v2; },
            [](const glm::vec4& v1, float value) -> glm::vec4 { return v1 - value; },
            [](float value, const glm::vec4& v1) -> glm::vec4 { return v1 - value; }
        ),
        sol::meta_function::multiplication, sol::overload(
            [](const glm::vec4& v1, const glm::vec4& v2) -> glm::vec4 { return v1 * v2; },
            [](const glm::vec4& v1, float value) -> glm::vec4 { return v1 * value; },
            [](float value, const glm::vec4& v1) -> glm::vec4 { return v1 * value; }
        ),
        sol::meta_function::division, sol::overload(
            [](const glm::vec4& v1, const glm::vec4& v2) -> glm::vec4 { return v1 / v2; },
            [](const glm::vec4& v1, float value) -> glm::vec4 { return v1 / value; },
            [](float value, const glm::vec4& v1) -> glm::vec4 { return v1 / value; }
        )
    );

    //TransformComponent
    luaState.new_usertype<GameEngine::TransformComponent>(
        sol::call_constructor,
        sol::constructors<GameEngine::TransformComponent(void), GameEngine::TransformComponent(const glm::vec3&, const glm::vec3&, const glm::vec3&)>(),
        "typename", [](){ puts("TransformComponent"); }
    );
}

void GameEngine::ScriptRegister::registerFunctions(sol::state& luaState, GameEngine::Scene* scene)
{
    //Input
    luaState.set_function("cpp_Input_isKeyPressed", &input_isKeyPressed);
    luaState.set_function("cpp_Input_getMouseX", sol::resolve<int(void)>(GameEngine::Input::getMouseX));
    luaState.set_function("cpp_Input_getMouseY", sol::resolve<int(void)>(GameEngine::Input::getMouseY));
    //Actor
    luaState.set_function("cpp_getScriptEngineTargetEntityID", &getScriptEngineTargetEntityID);
    luaState.set_function("cpp_actor_getComponent", &test);

    // luaState.set_function("cpp_getTemp", [&](sol::this_state s) {
    //     return sol::make_reference(s, std::ref(tempVec));
    // });
}

void GameEngine::ScriptRegister::registerComponents()
{
}


void GameEngine::ScriptRegister::setTargetEntityID(uint32_t id)
{
    scriptRegisterData.targetEntityID = id;
}
