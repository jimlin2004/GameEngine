#include "../include/ActorComponent/inputComponent/InputComponent.h"

GameEngine::InputComponent::InputComponent(): Component()
{

}

void GameEngine::InputComponent::bindKeyEvent(int key, std::function<void()> func)
{
    GEngine->addKeyEvent(key, func);
    return;
}