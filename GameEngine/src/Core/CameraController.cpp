#include "Core/CameraController.h"

GameEngine::CameraController::CameraController()
    : cameraPtr(nullptr)
    , transformComponentPtr(nullptr)
{
}

GameEngine::CameraController::CameraController(GameEngine::Camera* camera)
    : cameraPtr(camera)
    , transformComponentPtr(nullptr)
{
}

void GameEngine::CameraController::setViewTarget(GameEngine::Camera* camera, GameEngine::TransformComponent* transformComponent)
{
    this->cameraPtr = camera;
    this->transformComponentPtr = transformComponent;
}

void GameEngine::CameraController::setViewTarget(GameEngine::CameraComponent* cameraComponent, GameEngine::TransformComponent* transformComponent)
{
    this->cameraPtr = &cameraComponent->camera;
    this->transformComponentPtr = transformComponent;
}

glm::mat4 GameEngine::CameraController::getViewProjection() const
{
    return glm::mat4();
}