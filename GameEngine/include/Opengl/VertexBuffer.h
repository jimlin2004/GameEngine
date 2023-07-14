#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "GL/glew.h"

namespace GameEngine
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();
        void generate(const void* vertices, unsigned int size);
        void generate(unsigned int size);
        void setData(const void* data, unsigned int size);
        void bind();
        void unbind();
    private:
        unsigned int id;
    };
}

#endif