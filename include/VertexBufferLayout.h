#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>

namespace GameEngine
{
    class VertexBufferElement
    {
    public:
        VertexBufferElement(unsigned int type, unsigned int count, bool normalized);
        ~VertexBufferElement();
    private:
        unsigned int count;
        unsigned int type;
        bool normalized;
    };
    
    class VertexBufferLayout
    {
    public:
        VertexBufferLayout();
        ~VertexBufferLayout();
        void push(unsigned int type, int count);
        unsigned int getStride();
        unsigned int stride;
        const std::vector<VertexBufferElement*>& getElements() const;
    private:
        std::vector<VertexBufferElement*> elements;
    };
}

#endif