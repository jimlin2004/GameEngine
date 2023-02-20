#include "Camera.h"

GameEngine::Camera::Camera()
    : GameEngine::GameObject::GameObject()
    , projectionMatrix(glm::mat4(1.0))
{

}

void GameEngine::Camera::setProjectionMatrix(float left, float right, float bottom, float top)
{
    this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}