#include "Snake.h"

Snake::Snake(float x, float y)
{
    this->x = x;
    this->y = y;
    this->mesh->bindMesh<GameEngine::Graphics::Rect>(50.0f, 50.0f);
    this->setInputEvent();
}

void Snake::setInputEvent()
{
    this->playerInputComponent->bindKeyEvent('w', std::bind(&Snake::up, this));
    this->playerInputComponent->bindKeyEvent('a', std::bind(&Snake::left, this));
    this->playerInputComponent->bindKeyEvent('s', std::bind(&Snake::down, this));
    this->playerInputComponent->bindKeyEvent('d', std::bind(&Snake::right, this));
}

void Snake::up()
{
    this->y += 10.f;
}

void Snake::left()
{
    this->x -= 10;
}

void Snake::down()
{
    this->y -= 10;
}

void Snake::right()
{
    this->x += 10;
}