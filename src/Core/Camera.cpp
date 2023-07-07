#include "Core/Camera.h"

GameEngine::Camera::Camera()
    : GameEngine::GameObject::GameObject()
    , projectionMatrix(glm::mat4(1.0f)), viewMatrix(glm::mat4(1.0f)), position({0.0f, 0.0f, 0.0f})
{
    this->viewProjectionMatrix = this->projectionMatrix * this->viewMatrix;
}

GameEngine::Camera::Camera(const glm::vec3& pos)
    : GameEngine::GameObject::GameObject()
    , projectionMatrix(glm::mat4(1.0f)), viewMatrix(glm::mat4(1.0f)), position(pos)
{
    this->viewProjectionMatrix = this->projectionMatrix * this->viewMatrix;
}

void GameEngine::Camera::updateViewMatrix()
{
    glm::mat4 trasform = glm::translate(glm::mat4(1.0f), this->position);
    this->viewMatrix = glm::inverse(trasform);
    this->updateViewProjectionMatrix();
}

void GameEngine::Camera::updateViewProjectionMatrix()
{
    this->viewProjectionMatrix = this->projectionMatrix * this->viewMatrix;
}

void GameEngine::Camera::setPosition(const glm::vec3& pos)
{
    this->position = pos;
    this->updateViewMatrix();
}

void GameEngine::Camera::setProjectionMatrix(float left, float right, float bottom, float top)
{
    this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    this->updateViewProjectionMatrix();
}