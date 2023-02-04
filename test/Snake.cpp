#include "Snake.h"

Snake::Snake(float x, float y, float width, float height)
    : Character(x, y, width, height), speed(1.0f), direction({1, 0})
{
    this->mesh->bindMesh<GameEngine::Graphics::Rect>(width, height);
    this->setInputEvent();
}

void Snake::setInputEvent()
{
    this->playerInputComponent->bindKeyEvent('w', std::bind(&Snake::up, this));
    this->playerInputComponent->bindKeyEvent('a', std::bind(&Snake::left, this));
    this->playerInputComponent->bindKeyEvent('s', std::bind(&Snake::down, this));
    this->playerInputComponent->bindKeyEvent('d', std::bind(&Snake::right, this));
}

void Snake::setSpeed(float speed)
{
    this->speed = speed;
}

void Snake::move()
{
    this->x += this->direction.x * this->speed;
    this->y += this->direction.y * this->speed;
}

void Snake::up()
{
    this->direction = {0, 1};
}

void Snake::left()
{
    this->direction = {-1, 0};
}

void Snake::down()
{
    this->direction = {0, -1};
}

void Snake::right()
{
    this->direction = {1, 0};
}