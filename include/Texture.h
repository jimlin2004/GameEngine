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
        GLenum internalFormat;
        GLenum dataFormat;
    public:
        Texture();
        Texture(unsigned int _width, unsigned int _height);
        ~Texture();
        void setData(void* data);
        void load(const char* const path, int filter);
        void bind(unsigned int slot = 0);
        void unbind();
        bool operator==(const Texture& other) const
        {
            return this->id == other.id;
        }
        inline unsigned int getWidth() const { return width; }
        inline unsigned int getHeight() const { return height; }
    };
}

#endif