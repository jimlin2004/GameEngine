#include "VertexArray.h"

GameEngine::VertexArray::VertexArray()
{

}

GameEngine::VertexArray::~VertexArray()
{

}

void GameEngine::VertexArray::addBuffer(VertexBuffer& VB, const VertexBufferLayout& layout)
{
    VB.bind();
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
}