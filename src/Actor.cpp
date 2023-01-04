#include "Actor.h"

GameEngine::Actor::Actor()
{
    this->x = 0.f;
    this->y = 0.f;
    this->material = nullptr;
    this->mesh = new Mesh(&this->x, &this->y);
}

GameEngine::Actor::Actor(float x, float y)
{
    this->x = x;
    this->y = y;
    this->material = nullptr;
    this->mesh = new Mesh(&this->x, &this->y);
}

GameEngine::Actor::Actor(float x, float y, Material* material, Mesh* mesh)
{
    this->x = x;
    this->y = y;
    this->material = material;
    this->mesh = mesh;
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
    // this->material->setX(x);
    // this->material->setY(y);
}

void GameEngine::Actor::bindMesh(GameEngine::Graphics::Graphics* graphics)
{
    this->mesh->bindMesh(graphics);
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

GameEngine::Character::Character(float x, float y, Material* material, Mesh* mesh): Actor(x, y, material, mesh)
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