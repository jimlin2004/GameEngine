#ifndef GE_GRAPHICS_H
#define GE_GRAPHICS_H

#include "../third_party/glm/glm.hpp"
#include "GameObject.h"
#include "GameEngineAPI/GameEngineAPI.h"
#include "Renderer.h"

namespace GameEngine
{
    namespace Graphics
    {
        struct Point2D
        {
            float x;
            float y;
        };

        class Graphics
        {
        protected:
            float* x;
            float* y;
            glm::vec4 color;
        public:
            Graphics();
            Graphics(float* x, float* y);
            ~Graphics();
            virtual void render() = 0;
            virtual void setColor(const glm::vec4& color);
        };

        class Rect: public Graphics
        {
        private:
            float width, height;
        public:
            Rect(float* x, float* y, float width, float height);
            void render() override;
        };
    }
}
#endif