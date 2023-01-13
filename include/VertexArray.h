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

        void addBuffer(VertexBuffer& VB, const VertexBufferLayout& layout);
    };
}

#endif