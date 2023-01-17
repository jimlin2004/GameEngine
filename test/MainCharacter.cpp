#include "MainCharacter.h"

MainCharacter::MainCharacter(float x, float y)
{
    this->x = x;
    this->y = y;
    this->mesh->bindMesh<GameEngine::Graphics::Rect>(50.0f, 50.0f);
    this->setInputEvent();
}

void MainCharacter::setInputEvent()
{
    this->playerInputComponent->bindKeyEvent('w', std::bind(&MainCharacter::test, this));
}

void MainCharacter::test()
{
    this->x += 10.f;
    // this->texture->setX(this->x);
}