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
        void setSpeed(float speed);
    };
}

#endif