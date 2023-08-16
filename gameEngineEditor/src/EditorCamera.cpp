#include "EditorCamera.h"

GameEngineEditor::EditorCamera::EditorCamera(float _aspectRatio)
    : GameEngine::Camera()
    , zoomLevel(10.0f)
    , aspectRatio(_aspectRatio)
    , viewMatrix(glm::mat4(1.0f))
    , transformComponent()
{
    this->setProjection(-(this->aspectRatio * this->zoomLevel), this->aspectRatio * this->zoomLevel, -(this->zoomLevel), this->zoomLevel);
    this->viewProjectionMatrix = this->projection * this->viewMatrix;
}

GameEngineEditor::EditorCamera::EditorCamera(const glm::vec3& pos)
    : GameEngine::Camera()
    , viewMatrix(glm::mat4(1.0f))
    , transformComponent()
{
    this->viewProjectionMatrix = this->projection * this->viewMatrix;
    this->transformComponent.translation = pos;
}

void GameEngineEditor::EditorCamera::updateViewMatrix()
{
    glm::mat4 trasform = glm::translate(glm::mat4(1.0f), this->transformComponent.translation);
    this->viewMatrix = glm::inverse(trasform);
    this->updateViewProjectionMatrix();
}

void GameEngineEditor::EditorCamera::updateViewProjectionMatrix()
{
    this->viewProjectionMatrix = this->projection * this->viewMatrix;
}

void GameEngineEditor::EditorCamera::setPosition(const glm::vec3& pos)
{
    this->transformComponent.translation = pos;
    this->updateViewMatrix();
}

void GameEngineEditor::EditorCamera::setProjectionMatrix(float left, float right, float bottom, float top)
{
    this->projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    this->updateViewProjectionMatrix();
}

void GameEngineEditor::EditorCamera::setX(float x)
{
    this->transformComponent.translation.x = x;
    this->updateViewMatrix();
}

void GameEngineEditor::EditorCamera::setY(float y)
{
    this->transformComponent.translation.y = y;
    this->updateViewMatrix();
}

void GameEngineEditor::EditorCamera::setZ(float z)
{
    this->transformComponent.translation.z = z;
    this->updateViewMatrix();
}

void GameEngineEditor::EditorCamera::resize(float width, float height)
{
    this->aspectRatio = width / height;
    this->setProjection(-(this->aspectRatio * this->zoomLevel), this->aspectRatio * this->zoomLevel, -(this->zoomLevel), this->zoomLevel);
}

void GameEngineEditor::EditorCamera::onScrollWheel(float x, float y)
{
    this->zoomLevel -= y * 0.25f;
    this->zoomLevel = std::max(this->zoomLevel, 0.25f);
    this->setProjection(-(this->aspectRatio * this->zoomLevel), this->aspectRatio * this->zoomLevel, -(this->zoomLevel), this->zoomLevel);
}
