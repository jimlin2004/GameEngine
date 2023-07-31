#ifndef EDITOR_CAMERA_H
#define EDITOR_CAMERA_H

#include "Core/Camera.h"
#include "Component/Component.h"

namespace GameEngineEditor
{
    class EditorCamera: public GameEngine::Camera
    {
        private:
            
            glm::mat4 viewMatrix;
            glm::mat4 viewProjectionMatrix;
        private:
            void updateViewMatrix();
            void updateViewProjectionMatrix();
        public:
            EditorCamera();
            EditorCamera(const glm::vec3& pos);
            inline const glm::mat4& getProjectionMatrix() const { return this->projection; }
            inline const glm::mat4& getViewMatrix() const { return viewMatrix; }
            inline const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix; }
            inline const glm::vec3& getPosition() const { return this->transformComponent.translation; }
            inline const glm::mat4 getTransform() const { return this->transformComponent.getTransform(); }
            void setPosition(const glm::vec3& pos);
            void setProjectionMatrix(float left, float right, float bottom, float top);
            void setX(float x);
            inline float getX() const { return this->transformComponent.translation.x; }
            void setY(float y);
            inline float getY() const { return this->transformComponent.translation.y; }
            void setZ(float z);
            inline float getZ() const { return this->transformComponent.translation.z; }
        
            GameEngine::TransformComponent transformComponent;
    };
}

#endif