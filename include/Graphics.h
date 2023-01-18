#ifndef GE_GRAPHICS_H
#define GE_GRAPHICS_H

#include <GL/glew.h>
#include "../third_party/glm/glm.hpp"
#include "../third_party/glm/gtc/matrix_transform.hpp"
#include "../third_party/glm/gtc/type_ptr.hpp"
#include "GameObject.h"
#include "GameEngineAPI/GameEngineAPI.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

namespace GameEngine
{
    namespace Graphics
    {
        class Graphics: public GameObject
        {
        protected:
            float* x;
            float* y;
        public:
            Graphics();
            Graphics(float* x, float* y);
            ~Graphics();
            virtual void render();
        };

        struct Point2D
        {
            float x, y;
        };

        /*
            author: JimLin
            作用: 用於在畫面上畫直線，非供mesh使用
            note: 僅支援改變color，無texture
        */
        class Line: public Graphics
        {
        private:
            float lineWidth;
            VertexArray* va;
            VertexBuffer* vb;
            Shader* shader;
        public:
            Line(float fromX, float fromY, float toX, float toY);
            ~Line();
            void setLineWidth(int _width);
            void render();
        };

        class Rect: public Graphics
        {
        public:
            float width, height; 
            Rect(float* x, float* y, float width, float height, bool isUseTexture = false);
            ~Rect();
            virtual void render() override;
        private:
            VertexArray* va;
            VertexBuffer* vb;
            IndexBuffer* ib;
            Shader* shader;
            Texture* texture;
            bool isUseTexture;
            glm::mat4 translateMat;
            glm::mat4 MVP;

            void init();
        };
    }
}
#endif