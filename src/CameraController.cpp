#include "CameraController.h"

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
    this->_camera->setPosition(this->_camera->getPosition() + (this->speed * vec));
}

void GameEngine::CameraController::setSpeed(float speed)
{
    this->speed = speed;
}