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
        Camera* _camera;
        float speed;
        TransformComponent transformComponent;
        glm::mat4 viewMatrix;
        glm::mat4 viewProjectionMatrix;
    public:
        CameraController();
        CameraController(Camera* camera);

        inline Camera* getCamera() const { return _camera; };
        void bindCamera(Camera* camera);
        void moveCamera(const glm::vec3& vec);
        void moveCameraX(float newX);
        void moveCameraY(float newY);
        void moveCameraZ(float newZ);
        inline float getCameraX() const { return this->transformComponent.translation.x; }
        inline float getCameraY() const { return this->transformComponent.translation.y; }
        inline float getCameraZ() const { return this->transformComponent.translation.z; }
        void setSpeed(float speed);
        glm::mat4 getViewProjection() const;
        inline glm::mat4 getTransform() const
        {
            return this->transformComponent.getTransform();
        }
    };
}

#endif