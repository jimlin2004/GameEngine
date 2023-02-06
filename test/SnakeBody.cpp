#include "SnakeBody.h"

SnakeBody::SnakeBody(float x, float y, float width, float height, unsigned int i, unsigned int j)
    : GameEngine::Actor(x, y, width, height), i(i), j(j), width(width), height(height)
{
    this->mesh->bindMesh<GameEngine::Graphics::Rect>(width, height);
}