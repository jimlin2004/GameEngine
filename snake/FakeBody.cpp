#include "FakeBody.h"

FakeBody::FakeBody(float x, float y, float width, float height, Direction current)
    : GameEngine::Actor(x, y, width, height), width(width), height(height), currentDirection(current)
{
    this->mesh->bindMesh<GameEngine::Graphics::Rect>(width, height);
    this->mesh->setColor({0.0f, 1.0f, 0.0f, 1.0f});
}