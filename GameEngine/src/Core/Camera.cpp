#include "Core/Camera.h"

GameEngine::Camera::Camera()
    : projection(glm::mat4(1.0f))
{
}

GameEngine::Camera::Camera(const glm::mat4& projection)
    : projection(projection)
{
}

void GameEngine::Camera::setProjection(float left, float right, float bottom, float top)
{
    this->projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}