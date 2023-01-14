#ifndef VERTEXARRAY
#define VERTEXARRAY

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace GameEngine
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();
        void generate();
        void bind();
        void unbind();
        void addBuffer(VertexBuffer& VB, const VertexBufferLayout& layout);
    private:
        unsigned int id;
    };
}

#endif