#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <vector>
#include "GL/glew.h"

namespace GameEngine
{
    class VertexBufferElement
    {
    public:
        VertexBufferElement(unsigned int type, unsigned int count, bool normalized);
        ~VertexBufferElement();
        unsigned int count;
        unsigned int type;
        bool normalized;
    };
    
    class VertexBufferLayout
    {
    public:
        VertexBufferLayout();
        ~VertexBufferLayout();
        void push(unsigned int type, unsigned int count);
        inline unsigned int getStride() const {return stride;};
        const std::vector<VertexBufferElement*>& getElements() const;
        unsigned int stride;
        static unsigned int getSizezOfType(unsigned int type);
    private:
        std::vector<VertexBufferElement*> elements;
    };
}

#endif