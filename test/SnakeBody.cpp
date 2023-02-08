#include "SnakeBody.h"

SnakeBody::SnakeBody(float x, float y, float width, float height, unsigned int i, unsigned int j, Direction current)
    : GameEngine::Actor(x, y, width, height), i(i), j(j), width(width), height(height), currentDirection(current), nextDirection(current)
{
    this->mesh->bindMesh<GameEngine::Graphics::Rect>(width, height);
}