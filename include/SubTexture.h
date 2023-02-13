#ifndef SUBTEXTURE_H
#define SUBTEXTURE_H

#include "glm/glm.hpp"
#include "Texture.h"

namespace GameEngine
{
    class SubTexture
    {
    public:
        SubTexture(Texture* _texture, const glm::vec2& min, const glm::vec2& max);
        ~SubTexture();
        const glm::vec2* getTextureCrood() const;
        Texture* getTexture();
        static SubTexture* createFromCroods(Texture* texture, const glm::vec2& croods, const glm::vec2& cellSize, const glm::vec2& spriteSize = {1, 1}); 
    private:
        Texture* texture;
        glm::vec2 textureCroods[4];
    };
};

#endif