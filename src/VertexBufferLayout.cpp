#include "VertexBufferLayout.h"

GameEngine::VertexBufferElement::VertexBufferElement(unsigned int type, unsigned int count, bool normalized)
{
    this->type = type;
    this->count = count;
    this->normalized = normalized;
}

GameEngine::VertexBufferLayout::VertexBufferLayout()
{
    this->stride = 0;
}

GameEngine::VertexBufferLayout::~VertexBufferLayout()
{

}

const std::vector<GameEngine::VertexBufferElement*>& GameEngine::VertexBufferLayout::getElements() const
{
    return this->elements;
}

void GameEngine::VertexBufferLayout::push(unsigned int type, int count)
{
    switch (type)
    {
    case GL_FLOAT:
        this->elements.push_back(new VertexBufferElement(GL_FLOAT, count, false));
        break;
    case GL_UNSIGNED_INT:
        this->elements.push_back(new VertexBufferElement(GL_UNSIGNED_INT, count, true));
        break;
    case GL_UNSIGNED_BYTE:
        this->elements.push_back(new VertexBufferElement(GL_UNSIGNED_BYTE, count, true));
        break;
    default:
        break;
    }
}

unsigned int GameEngine::VertexBufferLayout::getStride()
{
    return this->stride;
}