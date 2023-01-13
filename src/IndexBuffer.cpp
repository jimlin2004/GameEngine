#include "IndexBuffer.h"

GameEngine::IndexBuffer::IndexBuffer()
{
    
}

GameEngine::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &(this->id));
}

void GameEngine::IndexBuffer::generate(const unsigned int* data, unsigned int count)
{
    this->count = count;
    glGenBuffers(1, &(this->id));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void GameEngine::IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void GameEngine::IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}