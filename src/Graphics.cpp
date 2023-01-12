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
    glGenBuffers(1, &(this->VBO));
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //usage
    // STATIC	資料只被設定一次，但會被使用很多次
    // DYNAMIC	資料被改變很多次，也被使用很多次
    // STREAM	資料每次繪製都會改變
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    std::string vertexShader = GameEngine::GEngine->shaderManager->loadShader("../asset/shader/test.vs");
    std::string fragmentShader = GameEngine::GEngine->shaderManager->loadShader("../asset/shader/test.fs");
    unsigned int shader = GameEngine::GEngine->shaderManager->createShader(vertexShader, fragmentShader);
    glUseProgram(shader);
}

void GameEngine::Graphics::Rect::render()
{
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}