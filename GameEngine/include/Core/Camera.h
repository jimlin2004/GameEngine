#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace GameEngine
{
    class Camera
    {
    public:
        Camera();
        Camera(const glm::mat4& projection);

        virtual ~Camera() = default;

        void setProjection(float left, float right, float bottom, float top);
        inline const glm::mat4& getProjection() const
        {
            return this->projection;
        }
    protected:
        glm::mat4 projection;
    };
}

#endif