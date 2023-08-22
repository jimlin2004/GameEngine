#include "TestActor.h"

#include "Script/ScriptEngine.h"

REGISTER_CLASS(TestActor)
TestActor::TestActor()
    : GameEngine::Actor()
{
}

void TestActor::destroy()
{
}

void TestActor::begin()
{
}

void TestActor::update(const float deltaTime)
{
    // printf("dll: %p\n", this->scene);
    // GameEngine::TransformComponent& transform = this->getComponent<GameEngine::TransformComponent>();
    // transform.translation.x += (10.0f * deltaTime);
    // if (GameEngine::Input::isKeyPressed(GameEngine::Key_A))
    //     transform.translation.x -= (100.0f * deltaTime);
    // if (GameEngine::Input::isKeyPressed(GameEngine::Key_D))
    //     transform.translation.x += (100.0f * deltaTime);
    // if (GameEngine::Input::isKeyPressed(GameEngine::Key_W))
    //     transform.translation.y += (100.0f * deltaTime);
    // if (GameEngine::Input::isKeyPressed(GameEngine::Key_S))
    //     transform.translation.y -= (100.0f * deltaTime);
    printf("Input in dll: %p\n", GameEngine::DLLtest);
}