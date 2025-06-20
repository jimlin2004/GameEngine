#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image/stb_image.h"
#include "GL/glew.h"

namespace GameEngine
{
    class Texture
    {
    private:
        uint32_t id;
        int width;
        int height;
        int bpp;
        unsigned char* pixels;
        GLenum internalFormat;
        GLenum dataFormat;
    public:
        Texture();
        Texture(uint32_t _width, uint32_t _height);
        ~Texture();
        void setData(void* data);
        void load(const char* const path, int filter);
        void bind(uint32_t slot = 0);
        void unbind();
        bool operator==(const Texture& other) const
        {
            return this->id == other.id;
        }
        inline uint32_t getWidth() const { return this->width; }
        inline uint32_t getHeight() const { return this->height; }
        inline uint32_t getTextureID() const { return this->id; }
    };
}

#endif