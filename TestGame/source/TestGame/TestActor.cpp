#include "TestActor.h"

REGISTER_CLASS(TestActor)
TestActor::TestActor()
    : GameEngine::Character()
{
}

void TestActor::destroy()
{
}

void TestActor::begin()
{
    printf("file: %s\n", __FILE__);
}

void TestActor::update(const float deltaTime)
{
    GameEngine::TransformComponent& transform = this->getComponent<GameEngine::TransformComponent>();
    if (GEngineCore::Input::isKeyPressed(GameEngine::Key_A))
        transform.translation.x -= (10.0f * deltaTime);
    if (GEngineCore::Input::isKeyPressed(GameEngine::Key_D))
        transform.translation.x += (10.0f * deltaTime);
    if (GEngineCore::Input::isKeyPressed(GameEngine::Key_W))
        transform.translation.y += (10.0f * deltaTime);
    if (GEngineCore::Input::isKeyPressed(GameEngine::Key_S))
        transform.translation.y -= (10.0f * deltaTime);
}