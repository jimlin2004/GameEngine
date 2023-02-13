#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GameObject.h"

namespace GameEngine
{
    class Camera: GameObject
    {
    private:
        glm::mat4 projectionMatrix;
    public:
        Camera();
        const glm::mat4& getProjectionMatrix() const { return this->projectionMatrix; }
        void setProjectionMatrix(float left, float right, float bottom, float top);
    };
}

#endif