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
    this->shader = new Shader();
    this->texture = new Texture();
    this->init();
    return;
}

GameEngine::Graphics::Rect::~Rect()
{
    delete this->va;
    delete this->vb;
    delete this->ib;
    delete this->shader;
    delete this->texture;
}

void GameEngine::Graphics::Rect::init()
{
    float vertices[] = {
          0.0f,   0.0f, 0.0f, 0.0f,//0
        100.0f,   0.0f, 1.0f, 0.0f,//1
        100.0f, 100.0f, 1.0f, 1.0f,//2
          0.0f, 100.0f, 0.0f, 1.0f //3
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->va->generate();
    this->vb->generate(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    layout.push(GL_FLOAT, 2);
    this->va->addBuffer(*(this->vb), layout);

    this->ib->generate(indices, 6);
    
    this->shader->generateShader("../asset/shader/test.vs", "../asset/shader/test.fs");
    this->shader->bind();
    this->shader->setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);
    this->shader->setUniformMat4f("u_MVP", GameEngine::PROJECTION_MATRIX);

    this->texture->load("../asset/texture/test.png", GL_NEAREST);
    this->texture->bind();
    this->shader->setUniform1i("u_texture", 0);

    glBindVertexArray(0);
    this->shader->unbind();
    this->vb->unbind();
    this->ib->unbind();
}

void GameEngine::Graphics::Rect::render()
{
    this->shader->bind();
    this->va->bind();
    this->ib->bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}