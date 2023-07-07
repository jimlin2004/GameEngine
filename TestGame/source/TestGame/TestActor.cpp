#include "TestActor.h"

#include "glm/glm.hpp"

TestActor::TestActor()
    : GameEngine::Character()
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
    GameEngine::TransformComponent& transform = this->getComponent<GameEngine::TransformComponent>();
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_A))
        transform.translation.x -= (100.0f * deltaTime);
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_D))
        transform.translation.x += (100.0f * deltaTime);
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_W))
        transform.translation.y += (100.0f * deltaTime);
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_S))
        transform.translation.y -= (100.0f * deltaTime);
}
