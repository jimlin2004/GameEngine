#include "Core/Camera.h"

GameEngine::Camera::Camera()
    : projection(glm::mat4(1.0f))
{
    this->setProjection(-(this->aspectRatio * this->orthographicSize), this->aspectRatio * this->orthographicSize, -(this->orthographicSize), this->orthographicSize);
}

GameEngine::Camera::Camera(const glm::mat4& projection)
    : projection(projection)
{
}

void GameEngine::Camera::setProjection(float left, float right, float bottom, float top)
{
    this->projection = glm::ortho(left, right, bottom, top, this->orthographicNear, this->orthographicFar);
}

void GameEngine::Camera::resize(float width, float height)
{
    this->aspectRatio = width / height;
    this->setProjection(-(this->aspectRatio * this->orthographicSize), this->aspectRatio * this->orthographicSize, -(this->orthographicSize), this->orthographicSize);
}

void GameEngine::Camera::setOrthographicSize(float value)
{
    this->orthographicSize = value;
    this->setProjection(-(this->aspectRatio * this->orthographicSize), this->aspectRatio * this->orthographicSize, -(this->orthographicSize), this->orthographicSize);
}

void GameEngine::Camera::setOrthographicNear(float value)
{
    this->orthographicNear = value;
    this->setProjection(-(this->aspectRatio * this->orthographicSize), this->aspectRatio * this->orthographicSize, -(this->orthographicSize), this->orthographicSize);
}

void GameEngine::Camera::setOrthographicFar(float value)
{
    this->orthographicFar = value;
    this->setProjection(-(this->aspectRatio * this->orthographicSize), this->aspectRatio * this->orthographicSize, -(this->orthographicSize), this->orthographicSize);
}

void GameEngine::Camera::setOrthographic(float size, float near, float far)
{
    this->orthographicSize = size;
    this->orthographicNear = near;
    this->orthographicFar = far;
    this->setProjection(-(this->aspectRatio * this->orthographicSize), this->aspectRatio * this->orthographicSize, -(this->orthographicSize), this->orthographicSize);
}

void GameEngine::Camera::setAspectRation(float value)
{
    this->aspectRatio = value;
    this->setProjection(-(this->aspectRatio * this->orthographicSize), this->aspectRatio * this->orthographicSize, -(this->orthographicSize), this->orthographicSize);
}
