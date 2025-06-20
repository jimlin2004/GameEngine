#include "Opengl/VertexBuffer.h"

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

void GameEngine::VertexBuffer::generate(unsigned int size)
{
    glGenBuffers(1, &(this->id));
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

void GameEngine::VertexBuffer::setData(const void* data, unsigned int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void GameEngine::VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void GameEngine::VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}