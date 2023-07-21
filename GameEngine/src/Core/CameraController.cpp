#include "Core/CameraController.h"

GameEngine::CameraController::CameraController()
    :_camera(nullptr), speed(0.0f)
{

}

GameEngine::CameraController::CameraController(GameEngine::Camera* camera)
    :_camera(camera), speed(0.0f)
{
    
}

void GameEngine::CameraController::bindCamera(GameEngine::Camera* camera)
{
    this->_camera = camera;
}

void GameEngine::CameraController::moveCamera(const glm::vec3& vec)
{
    this->transformComponent.translation += (this->speed * vec);
}

void GameEngine::CameraController::moveCameraX(float newX)
{
    this->transformComponent.translation.x = newX;
}

void GameEngine::CameraController::moveCameraY(float newY)
{
    this->transformComponent.translation.y = newY;
}

void GameEngine::CameraController::moveCameraZ(float newZ)
{
    this->transformComponent.translation.z = newZ;
}

void GameEngine::CameraController::setSpeed(float speed)
{
    this->speed = speed;
}
glm::mat4 GameEngine::CameraController::getViewProjection() const
{
    return glm::mat4();
}