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

void GameEngine::VertexBufferLayout::push(unsigned int type, unsigned int count)
{
    switch (type)
    {
    case GL_FLOAT:
        this->elements.push_back(new VertexBufferElement(GL_FLOAT, count, false));
        this->stride += count * VertexBufferLayout::getSizezOfType(GL_FLOAT);
        break;
    case GL_UNSIGNED_INT:
        this->elements.push_back(new VertexBufferElement(GL_UNSIGNED_INT, count, true));
        this->stride += count * VertexBufferLayout::getSizezOfType(GL_UNSIGNED_INT);
        break;
    case GL_UNSIGNED_BYTE:
        this->elements.push_back(new VertexBufferElement(GL_UNSIGNED_BYTE, count, true));
        this->stride += count * VertexBufferLayout::getSizezOfType(GL_UNSIGNED_BYTE);
        break;
    default:
        break;
    }
}

unsigned int GameEngine::VertexBufferLayout::getSizezOfType(unsigned int type)
{
    switch (type)
    {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
        default: return 0;
    }
}