/*
author
    JimLin
lastest modify
    -2023/01/16
*/

#include "Texture.h"

GameEngine::Texture::Texture()
    : id(0), width(0), height(0), bpp(0), pixels(nullptr), internalFormat(0), dataFormat(0)
{

}

GameEngine::Texture::Texture(unsigned int _width, unsigned int _height)
    : id(0), width(_width), height(_height), bpp(0), pixels(nullptr)
{
    this->internalFormat = GL_RGBA8;
    this->dataFormat = GL_RGBA;
    // glCreateTextures(GL_TEXTURE_2D, 1, &this->id);
    // glTextureStorage2D(this->id, 1, this->internalFormat, this->width, this->height);
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    GLubyte texData[] = { 255, 255, 255, 255 };
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, this->width, this->height, 0, this->dataFormat, GL_UNSIGNED_BYTE, NULL);
}

GameEngine::Texture::~Texture()
{

}

/*
parameter
    -const char* const path: file path
    -int filter: GL_LINEAR or GL_NEAREST
*/
void GameEngine::Texture::load(const char* const path, int filter)
{
    stbi_set_flip_vertically_on_load(1);
    this->pixels = stbi_load(path, &this->width, &this->height, &this->bpp, 4);
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (this->pixels)
        stbi_image_free(this->pixels);
}

void GameEngine::Texture::setData(void* data)
{
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->width, this->height, this->dataFormat, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GameEngine::Texture::bind(unsigned int slot/*= 0*/)
{
    glActiveTexture(GL_TEXTURE0 + slot); //slot: 0~31(共32)
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void GameEngine::Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}