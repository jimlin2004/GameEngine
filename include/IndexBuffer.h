#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "GL/glew.h"
#include <stdio.h>

namespace GameEngine
{
    class IndexBuffer
    {
    public:
        IndexBuffer();
        ~IndexBuffer();
        void generate(const unsigned int* data, unsigned int count);
        void bind();
        void unbind();
        inline unsigned int getCount() const { return count; }
    private:
        unsigned int id;
        unsigned int count;
    };
}

#endif