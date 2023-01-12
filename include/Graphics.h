#ifndef GE_GRAPHICS_H
#define GE_GRAPHICS_H

// #include <GL/gl.h>
// #include <GL/glu.h>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include "GameEngineAPI/GameEngineAPI.h"

#include "GameObject.h"

namespace GameEngine
{
    namespace Graphics
    {
        class Graphics: public GameObject
        {
        protected:
            float x;
            float y;
        public:
            Graphics(float x, float y);
            virtual void render();
        };

        class Rect: public Graphics
        {
        public:
            float width, height; 
            Rect(float x, float y, float width, float height);
            virtual void render() override;
        private:
            GLuint VBO;
            void processVBO();
        };
    }
}
#endif