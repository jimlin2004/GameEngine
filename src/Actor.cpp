#include "Actor.h"

GameEngine::Actor::Actor()
{
    this->x = 0.f;
    this->y = 0.f;
    this->texture = nullptr;
}

GameEngine::Actor::Actor(float x, float y)
{
    this->x = x;
    this->y = y;
    this->texture = nullptr;
}

GameEngine::Actor::Actor(float x, float y, Graphics::Graphics* graphics)
{
    this->x = x;
    this->y = y;
    this->texture = graphics;
}

void GameEngine::Actor::HandleEvent()
{
    return;
}

void GameEngine::Actor::render()
{
    this->texture->render();
    return;
}

void GameEngine::Actor::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
    this->texture->setX(x);
    this->texture->setY(y);
}
//==================Character===============================

GameEngine::Character::Character(): Actor()
{
    this->playerInputComponent = new InputComponent();
    return;
}

GameEngine::Character::Character(float x, float y): Actor(x, y)
{
    this->playerInputComponent = new InputComponent();
    return;
}

GameEngine::Character::Character(float x, float y, Graphics::Graphics* graphics): Actor(x, y, graphics)
{
    this->playerInputComponent = new InputComponent();
    return;
}

void GameEngine::Character::setInputEvent()
{
    return;
}