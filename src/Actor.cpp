#include "Actor.h"

GameEngine::Actor::Actor()
{
    this->x = 0.f;
    this->y = 0.f;
    this->material = nullptr;
    this->mesh = new Mesh(&this->x, &this->y, 0.0f, 0.0f);
}

GameEngine::Actor::Actor(float x, float y)
{
    this->x = x;
    this->y = y;
    this->material = nullptr;
    this->mesh = new Mesh(&this->x, &this->y, 0.0f, 0.0f);
}

GameEngine::Actor::Actor(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->material = nullptr;
    this->mesh = new Mesh(&this->x, &this->y, width, height);
}

GameEngine::Actor::~Actor()
{
    delete this->material;
    delete this->mesh;
}

void GameEngine::Actor::HandleEvent()
{
    return;
}

void GameEngine::Actor::render()
{
    this->mesh->render();
    return;
}

void GameEngine::Actor::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
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

GameEngine::Character::Character(float x, float y, float width, float height): Actor(x, y, width, height)
{
    this->playerInputComponent = new InputComponent();
    return;
}

GameEngine::Character::~Character()
{
    delete this->playerInputComponent;
    return;
}

void GameEngine::Character::setInputEvent()
{
    return;
}