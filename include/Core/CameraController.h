#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "glm/glm.hpp"

#include "GameObject.h"
#include "Camera.h"

namespace GameEngine
{
    class CameraController: GameObject
    {
    private:
        Camera* _camera;
        float speed;
    public:
        CameraController();
        CameraController(Camera* camera);

        inline Camera* getCamera() const { return _camera; };
        void bindCamera(Camera* camera);
        void moveCamera(const glm::vec3& vec);
        void moveCameraX(float newX);
        void moveCameraY(float newY);
        void moveCameraZ(float newZ);
        inline float getCameraX() const { return this->_camera->transformComponent.translation.x; }
        inline float getCameraY() const { return this->_camera->transformComponent.translation.y; }
        inline float getCameraZ() const { return this->_camera->transformComponent.translation.z; }
        void setSpeed(float speed);
        inline glm::mat4 getTransform() const
        {
            return this->_camera->transformComponent.getTransform();
        }
    };
}

#endif