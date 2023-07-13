#include "Core/Camera.h"

GameEngine::Camera::Camera()
    : GameEngine::GameObject::GameObject()
    , projectionMatrix(glm::mat4(1.0f)), viewMatrix(glm::mat4(1.0f))
    , transformComponent()
{
    this->viewProjectionMatrix = this->projectionMatrix * this->viewMatrix;
}

GameEngine::Camera::Camera(const glm::vec3& pos)
    : GameEngine::GameObject::GameObject()
    , projectionMatrix(glm::mat4(1.0f)), viewMatrix(glm::mat4(1.0f))
    , transformComponent()
{
    this->viewProjectionMatrix = this->projectionMatrix * this->viewMatrix;
    this->transformComponent.translation = pos;
}

void GameEngine::Camera::updateViewMatrix()
{
    glm::mat4 trasform = glm::translate(glm::mat4(1.0f), this->transformComponent.translation);
    this->viewMatrix = glm::inverse(trasform);
    this->updateViewProjectionMatrix();
}

void GameEngine::Camera::updateViewProjectionMatrix()
{
    this->viewProjectionMatrix = this->projectionMatrix * this->viewMatrix;
}

void GameEngine::Camera::setPosition(const glm::vec3& pos)
{
    this->transformComponent.translation = pos;
    this->updateViewMatrix();
}

void GameEngine::Camera::setProjectionMatrix(float left, float right, float bottom, float top)
{
    this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    this->updateViewProjectionMatrix();
}

void GameEngine::Camera::setX(float x)
{
    this->transformComponent.translation.x = x;
    this->updateViewMatrix();
}

void GameEngine::Camera::setY(float y)
{
    this->transformComponent.translation.y = y;
    this->updateViewMatrix();
}

void GameEngine::Camera::setZ(float z)
{
    this->transformComponent.translation.z = z;
    this->updateViewMatrix();
}
