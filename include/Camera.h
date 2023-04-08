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
        glm::vec3 position;
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 viewProjectionMatrix;
    private:
        void updateViewMatrix();
        void updateViewProjectionMatrix();
    public:
        Camera();
        Camera(const glm::vec3& pos);
        inline const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
        inline const glm::mat4& getViewMatrix() const { return viewMatrix; }
        inline const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix; }
        inline const glm::vec3& getPosition() const { return position; }
        void setPosition(const glm::vec3& pos);
        void setProjectionMatrix(float left, float right, float bottom, float top);
    };
}

#endif