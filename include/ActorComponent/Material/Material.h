#ifndef MATERIAL_H
#define MATERIAL_H

#include "../../Graphics.h"

namespace GameEngine
{
    class Material
    {
    public:
        Material();
        ~Material();
        void render();
    private:
        Graphics::Graphics* texture;
    };
}

#endif