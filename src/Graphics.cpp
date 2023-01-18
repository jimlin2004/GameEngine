#include "Graphics.h"

GameEngine::Graphics::Graphics::Graphics()
{
    this->x = this->y = nullptr;
}

GameEngine::Graphics::Graphics::Graphics(float* x, float* y)
{
    this->x = x;
    this->y = y;
}

GameEngine::Graphics::Graphics::~Graphics()
{
    delete this->x;
    delete this->y;
}

void GameEngine::Graphics::Graphics::render()
{
    return;
}

GameEngine::Graphics::Line::Line(float fromX, float fromY, float toX, float toY): Graphics()
{
    this->lineWidth = 1.0f;
    this->va = new VertexArray();
    this->vb = new VertexBuffer();
    this->shader = new Shader();
    float vertices[] = {
        fromX, fromY,
          toX,   toY 
    };
    this->va->generate();
    this->vb->generate(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    this->va->addBuffer(*(this->vb), layout);
    this->shader->generateShader("../asset/shader/line/line.vs", "../asset/shader/line/line.fs");
    this->shader->bind();
    this->shader->setUniformMat4f("u_MVP", GameEngine::PROJECTION_MATRIX);
    this->shader->setUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);
    this->va->unbind();
    this->shader->unbind();
    this->vb->unbind();
}

GameEngine::Graphics::Line::~Line()
{
    delete this->va;
    delete this->vb;
    delete this->shader;
}

void GameEngine::Graphics::Line::render()
{
    this->shader->bind();
    this->va->bind();

    glLineWidth(this->lineWidth);
    glDrawArrays(GL_LINES, 0, 2);
}

void GameEngine::Graphics::Line::setLineWidth(int _width)
{
    this->lineWidth = _width;
}

GameEngine::Graphics::Rect::Rect(float* x, float* y, float width, float height, bool isUseTexture): Graphics(x, y)
{
    this->width = width;
    this->height = height;
    this->isUseTexture = isUseTexture;
    this->va = new VertexArray();
    this->vb = new VertexBuffer();
    this->ib = new IndexBuffer();
    this->shader = new Shader();
    this->texture = new Texture();
    this->translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(*this->x, *this->y, 0.0f));
    this->MVP = PROJECTION_MATRIX * this->translateMat;
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
               0.0f,         0.0f, 0.0f, 0.0f,//0
        this->width,         0.0f, 1.0f, 0.0f,//1
        this->width, this->height, 1.0f, 1.0f,//2
               0.0f, this->height, 0.0f, 1.0f //3
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    this->va->generate();
    this->vb->generate(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    layout.push(GL_FLOAT, 2);
    this->va->addBuffer(*(this->vb), layout);

    this->ib->generate(indices, 6);
    
    if (this->isUseTexture)
        this->shader->generateShader("../asset/shader/rect/rect_with_texture.vs", "../asset/shader/rect/rect_with_texture.fs");
    else
        this->shader->generateShader("../asset/shader/rect/rect.vs", "../asset/shader/rect/rect.fs");
    this->shader->bind();
    
    this->shader->setUniformMat4f("u_MVP", this->MVP);
    if (this->isUseTexture)
    {
        this->texture->load("../asset/texture/test.png", GL_NEAREST);
        this->texture->bind();
        this->shader->setUniform1i("u_texture", 0);
    }
    else
        this->shader->setUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);

    this->va->unbind();
    this->shader->unbind();
    this->vb->unbind();
    this->ib->unbind();
}

void GameEngine::Graphics::Rect::render()
{
    this->translateMat = glm::translate(glm::mat4(1.0), glm::vec3(*this->x, *this->y, 0.0f));
    this->MVP = PROJECTION_MATRIX * this->translateMat;
    this->shader->bind();
    this->shader->setUniformMat4f("u_MVP", this->MVP);
    this->va->bind();
    this->ib->bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}