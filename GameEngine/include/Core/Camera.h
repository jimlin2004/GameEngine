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
        virtual void resize(float width, float height);
        inline const glm::mat4& getProjection() const
        {
            return this->projection;
        }
        void setOrthographicSize(float value);
        void setOrthographicNear(float value);
        void setOrthographicFar(float value);
        void setOrthographic(float size, float near, float far);
        void setAspectRation(float value);
        inline const float getOrthographicSize() const { return this->orthographicSize; }
        inline const float getOrthographicNear() const { return this->orthographicNear; }
        inline const float getOrthographicFar() const { return this->orthographicFar; }
        inline const float getAspectRatio() const { return this->aspectRatio; }
    protected:
        glm::mat4 projection;
        float aspectRatio = 1.0f;
        float orthographicSize = 5.0f;
        float orthographicNear = -1.0f;
        float orthographicFar  = 1.0f;
    };
}

#endif