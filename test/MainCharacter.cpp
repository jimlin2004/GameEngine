#include "MainCharacter.h"

MainCharacter::MainCharacter(float x, float y)
{
    this->texture = new GameEngine::Graphics::Rect(x, y, 50.f, 50.f);
    this->setInputEvent();
}

void MainCharacter::setInputEvent()
{
    this->playerInputComponent->bindKeyEvent('w', std::bind(&MainCharacter::test, this));
}

void MainCharacter::test()
{
    this->x += 10.f;
    this->texture->setX(this->x);
}