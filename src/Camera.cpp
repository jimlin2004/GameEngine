#include "Camera.h"

GameEngine::Camera::Camera(): GameEngine::GameObject::GameObject()
{

}

void GameEngine::Camera::setProjectionMatrix(float left, float right, float bottom, float top)
{
    this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}