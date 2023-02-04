#include "SubTexture.h"

GameEngine::SubTexture::SubTexture(Texture* _texture, const glm::vec2& min, const glm::vec2& max)
    :texture(_texture)
{
    this->textureCroods[0] = { min.x, min.y };
    this->textureCroods[1] = { max.x, min.y };
    this->textureCroods[2] = { max.x, max.y };
    this->textureCroods[3] = { min.x, max.y };
}

GameEngine::SubTexture::~SubTexture()
{
    
}

const glm::vec2* GameEngine::SubTexture::getTextureCrood() const
{
    return this->textureCroods;
}

GameEngine::Texture* GameEngine::SubTexture::getTexture()
{
    return this->texture;
}

GameEngine::SubTexture* GameEngine::SubTexture::createFromCroods(GameEngine::Texture* texture, const glm::vec2& croods, const glm::vec2& cellSize, const glm::vec2& spriteSize/* = {1, 1}*/)
{
    glm::vec2 min = { 
        (croods.x * cellSize.x) / texture->getWidth(), 
        (croods.y * cellSize.y) / texture->getHeight()
    };
    glm::vec2 max = {
        ((croods.x + spriteSize.x) * cellSize.x) / texture->getWidth(), 
        ((croods.y + spriteSize.y) * cellSize.y) / texture->getHeight()
    };
    return new GameEngine::SubTexture(texture, min, max);
}