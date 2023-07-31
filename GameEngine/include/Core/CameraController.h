#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "glm/glm.hpp"

#include "GameObject.h"
#include "Component/Component.h"
#include "Camera.h"

namespace GameEngine
{
    class CameraController: GameObject
    {
    private:
        Camera* cameraPtr;
        TransformComponent* transformComponentPtr;
        glm::mat4 viewMatrix;
        glm::mat4 viewProjectionMatrix;
    public:
        CameraController();
        CameraController(Camera* camera);

        inline Camera* getCamera() const { return this->cameraPtr; };
        void setViewTarget(Camera* camera, TransformComponent* transformComponent);
        void setViewTarget(CameraComponent* cameraComponent, TransformComponent* transformComponent);
        glm::mat4 getViewProjection() const;
        inline glm::mat4 getTransform() const
        {
            return this->transformComponentPtr->getTransform();
        }
    };
}

#endif