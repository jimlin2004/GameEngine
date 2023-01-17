#ifndef MESH_H
#define MESH_H

#include "../../Graphics.h"

namespace GameEngine
{
    /*
        author: JimLin
        用於將Graphics 綁定至Actor上
    */
    class Mesh
    {
    public:
        Mesh();
        Mesh(float* rootX, float* rootY, float width, float height);
        ~Mesh();

        template<class T>
        void bindMesh()
        {
            this->graphics = new T(this->rootX, this->rootY, this->width, this->height);
        }
        template<class T>
        void bindMesh(float width, float height)
        {
            this->width = width;
            this->height = height;
            this->graphics = new T(this->rootX, this->rootY, this->width, this->height);
        }
        void render();
    private:
        float* rootX;
        float* rootY;
        float width, height;
        Graphics::Graphics* graphics;
    };
}

#endif