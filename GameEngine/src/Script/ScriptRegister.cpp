#include "Script/ScriptRegister.h"

#include "Core/GameEngineCore.h"
#include "Scene/Scene.h"
#include "glm/glm.hpp"
#include "box2d/box2d.h"

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

void GameEngine::Script::ScriptRegister::setTargetEntityID(uint32_t id)
{
    scriptRegisterData.targetEntityID = id;
}

//不清楚為什麼不能直接用GameEngine::Input::isKeyPressed引入Lua，改用此函式包裝
static inline bool input_isKeyPressed(uint32_t keyCode)
{
    return GameEngine::Input::isKeyPressed((GameEngine::KeyCode)keyCode);
}

void GameEngine::Script::ScriptRegister::registerClass(sol::state &luaState, GameEngine::Scene* scene)
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
        "TransformComponent",
        sol::call_constructor,
        sol::constructors<GameEngine::TransformComponent(), GameEngine::TransformComponent(const glm::vec3&, const glm::vec3&, const glm::vec3&)>(),
        "position", &GameEngine::TransformComponent::translation,
        "rotation", &GameEngine::TransformComponent::rotation,
        "scale", &GameEngine::TransformComponent::scale
    );

    //Rigidbody2DComponent
    luaState.new_usertype<GameEngine::Rigidbody2DComponent>(
        "Rigidbody2DComponent",
        sol::call_constructor,
        sol::constructors<GameEngine::Rigidbody2DComponent()>(),
        "getLinearVelocity", [](const GameEngine::Rigidbody2DComponent& component) {
            b2Body* body = (b2Body*)component.runtimeBody;
            const b2Vec2& linearVelocity = body->GetLinearVelocity();
            return glm::vec2{linearVelocity.x, linearVelocity.y};
        },
        "applyLinearImpulseToCenter", [](const GameEngine::Rigidbody2DComponent& component, const glm::vec2& impulse, bool wake) {
            b2Body* body = (b2Body*)component.runtimeBody;
            body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), wake);
        }
    );
}

void GameEngine::Script::ScriptRegister::registerFunctions(sol::state& luaState, GameEngine::Scene* scene)
{
    //Input
    luaState.set_function("cpp_Input_isKeyPressed", &input_isKeyPressed);
    luaState.set_function("cpp_Input_getMouseX", sol::resolve<int(void)>(GameEngine::Input::getMouseX));
    luaState.set_function("cpp_Input_getMouseY", sol::resolve<int(void)>(GameEngine::Input::getMouseY));
    //Actor
    luaState.set_function("cpp_getScriptEngineTargetEntityID", &getScriptEngineTargetEntityID);
    luaState.set_function("cpp_actor_getComponent", sol::overload(
        [scene](const GameEngine::TransformComponent& component, uint32_t entityID, sol::this_state s){
            GameEngine::TransformComponent& transformComponent = scene->queryActorComponent<GameEngine::TransformComponent>((entt::entity)entityID);
            return sol::make_reference(s, std::ref(transformComponent));
        },
        [scene](const GameEngine::Rigidbody2DComponent& component, uint32_t entityID, sol::this_state s){
            GameEngine::Rigidbody2DComponent& rigidbody2DComponent = scene->queryActorComponent<GameEngine::Rigidbody2DComponent>((entt::entity)entityID);
            return sol::make_reference(s, std::ref(rigidbody2DComponent));
        }
    ));

    // luaState.set_function("cpp_getTemp", [&](sol::this_state s) {
    //     return sol::make_reference(s, std::ref(tempVec));
    // });
}

void GameEngine::Script::ScriptRegister::registerComponents()
{
}