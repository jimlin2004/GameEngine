#ifndef MESH_H
#define MESH_H

#include "../../Graphics.h"

namespace GameEngine
{
    class Mesh
    {
    public:
        Mesh();
        Mesh(float* rootX, float* rootY);
        Mesh(float* rootX, float* rootY, Graphics::Graphics* graphics);
        ~Mesh();

        void bindMesh(Graphics::Graphics* graphics);
        void render();
    private:
        float* rootX;
        float* rootY;
        Graphics::Graphics* graphics;
    };
}

#endif