#ifndef TEXTURE_H
#define TEXTURE_H

#include "../third_party/stb_image/stb_image.h"
#include <GL/glew.h>

namespace GameEngine
{
    class Texture
    {
    private:
        unsigned int id;
        int width;
        int height;
        int bpp;
        unsigned char* pixels;
    public:
        Texture();
        ~Texture();
        void load(const char* const path, int filter);
        void bind(unsigned int slot = 0);
        void unbind();
    };
}

#endif