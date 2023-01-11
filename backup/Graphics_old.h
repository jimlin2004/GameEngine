#ifndef GE_GRAPHICS_OLD_H
#define GE_GRAPHICS_OLD_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "GameObject.h"

namespace GameEngine
{
    namespace Graphics
    {
        class Color
        {
        public:
            GLclampf r, g, b, a;
            Color(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
        };

        class Graphics: public GameObject
        {
        protected:
            float* x;
            float* y;
            float offsetX, offsetY;
            float width, height;
            Color* color;
        public:
            Graphics();
            Graphics(float* x, float* y);
            Graphics(float* x, float* y, Color* color);
            Graphics(float* x, float* y, float width, float height);
            Graphics(float* x, float* y, float width, float height, Color* color);
            ~Graphics();
            void setOffestX(float x);
            float getX();
            void setOffsetY(float y);
            float getY();
            virtual void render();

        };

        class Rect: public Graphics
        {
        public:
            Rect();
            Rect(float x, float y);
            Rect(float x, float y, Color* color);
            Rect(float x, float y, float width, float height);
            Rect(float x, float y, float width, float height, Color* color);
            virtual void render() override;
        };

        class Texture: public Graphics
        {
        public:
            Texture(float x, float y);
            ~Texture();
            unsigned int load(const char* fileName);
            virtual void render() override;
        private:
            unsigned int textureID;
        };
    }

    /*以下為Graphics處理時用的function*/
    void filpSurface(SDL_Surface* surface);
}





#endif