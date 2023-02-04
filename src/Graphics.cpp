#include "Graphics.h"

GameEngine::Graphics::Graphics::Graphics()
    : x(nullptr), y(nullptr), color({1.0f, 1.0f, 1.0f, 1.0f})
{

}

GameEngine::Graphics::Graphics::Graphics(float* x, float* y)
    : x(x), y(y), color({1.0f, 1.0f, 1.0f, 1.0f})
{

}

GameEngine::Graphics::Graphics::~Graphics()
{
    delete this->x;
    delete this->y;
}

void GameEngine::Graphics::Graphics::setColor(const glm::vec4& color)
{
    this->color = color;
}

GameEngine::Graphics::Rect::Rect(float* x, float* y, float width, float height)
    : GameEngine::Graphics::Graphics(x, y), width(width), height(height)
{

}

void GameEngine::Graphics::Rect::render()
{
    GameEngine::Renderer::drawQuad({*this->x, *this->y}, {this->width, this->height}, this->color);
}