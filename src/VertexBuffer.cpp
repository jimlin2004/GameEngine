#include "VertexBuffer.h"

GameEngine::VertexBuffer::VertexBuffer()
{
    
}

GameEngine::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &(this->id));
}

void GameEngine::VertexBuffer::generate(const void* vertices, unsigned int size)
{
    glGenBuffers(1, &(this->id));
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void GameEngine::VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void GameEngine::VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}