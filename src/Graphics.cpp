#include "Graphics.h"

GameEngine::Graphics::Graphics::Graphics(float x, float y)
{
    this->x = x;
    this->y = y;
}

void GameEngine::Graphics::Graphics::render()
{
    return;
}

GameEngine::Graphics::Rect::Rect(float x, float y, float width, float height): Graphics(x, y)
{
    this->width = width;
    this->height = height;
    this->va = new VertexArray();
    this->vb = new VertexBuffer();
    this->ib = new IndexBuffer();
    this->processVBO();
    return;
}

void GameEngine::Graphics::Rect::processVBO()
{
    float vertices[] = {
        -0.5f, -0.5f, //0
         0.5f, -0.5f, //1
         0.5f,  0.5f, //2
         -0.5f, 0.5f  //3
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    // glGenVertexArrays(1, &(this->VAO));
    // glBindVertexArray(this->VAO);
    this->va->generate();
    this->vb->generate(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    this->va->addBuffer(*(this->vb), layout);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    this->ib->generate(indices, 6);
    

    std::string vertexShader = GameEngine::GEngine->shaderManager->loadShader("../asset/shader/test.vs");
    std::string fragmentShader = GameEngine::GEngine->shaderManager->loadShader("../asset/shader/test.fs");
    this->shader = GameEngine::GEngine->shaderManager->createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GameEngine::Graphics::Rect::render()
{
    glUseProgram(this->shader);
    // glBindVertexArray(this->VAO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ib->id);
    this->va->bind();
    this->ib->bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}