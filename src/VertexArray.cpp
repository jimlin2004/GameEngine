#include "VertexArray.h"

GameEngine::VertexArray::VertexArray()
{

}

GameEngine::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &(this->id));
}

void GameEngine::VertexArray::generate()
{
    glGenVertexArrays(1, &(this->id));
}

void GameEngine::VertexArray::bind()
{
    glBindVertexArray(this->id);
}

void GameEngine::VertexArray::unbind()
{
    glBindVertexArray(0);
}

void GameEngine::VertexArray::addBuffer(VertexBuffer& VB, const VertexBufferLayout& layout)
{
    this->bind();
    VB.bind();
    const std::vector<GameEngine::VertexBufferElement*>& elements = layout.getElements();
    const GameEngine::VertexBufferElement* element;
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); ++i)
    {
        element = elements[i];
        // glEnableVertexAttribArray(i);
        glEnableVertexArrayAttrib(this->id, i);
        glVertexAttribPointer(i, element->count, element->type, element->normalized, layout.getStride(), (const void*)offset);
        offset += element->count * VertexBufferLayout::getSizezOfType(element->type);
    }
}