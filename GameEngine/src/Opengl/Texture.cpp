/*
author
    JimLin
lastest modify
    -2023/01/16
*/

#include "Opengl/Texture.h"

#include <filesystem>
#include "GameEngineAPI/GameEngineAPI.h"

GameEngine::Texture::Texture()
    : id(0), width(0), height(0), bpp(0), pixels(nullptr)
    , internalFormat(GL_RGBA8), dataFormat(GL_RGBA)
{

}

GameEngine::Texture::Texture(uint32_t _width, uint32_t _height)
    : id(0), width(_width), height(_height), bpp(0), pixels(nullptr)
    , internalFormat(GL_RGBA8), dataFormat(GL_RGBA)
{
    // glCreateTextures(GL_TEXTURE_2D, 1, &this->id);
    // glTextureStorage2D(this->id, 1, this->internalFormat, this->width, this->height);
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // GLubyte texData[] = { 255, 255, 255, 255 };
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
    std::string fileName  = std::filesystem::u8path(std::string(path)).filename().u8string();
    uint32_t registeredID = GameEngine::GEngine->textureManager->exists(fileName);
    if (registeredID != 0U)
    {
        //此圖片已註冊過
        this->id = registeredID;
        return;
    }

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

    //保留texture資料給Editor用
    GameEngine::GEngine->textureManager->registerTexture(this->id, fileName);
}

void GameEngine::Texture::setData(void* data)
{
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->width, this->height, this->dataFormat, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GameEngine::Texture::bind(uint32_t slot/*= 0*/)
{
    glActiveTexture(GL_TEXTURE0 + slot); //slot: 0~31(共32)
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void GameEngine::Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}