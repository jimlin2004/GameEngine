#include "SnakeGame.h"

SnakeGame::SnakeGame(const char* title, int width, int height): GameBase(title, width, height)
{
    
}

void SnakeGame::begin()
{
    this->snake = GameEngine::GEngine->spawnActor<Snake>(new GameEngine::Vector(0.f, 0.f, 0.f));
    this->grid = new Grid();
}

void SnakeGame::gameContext()
{
    glClear(GL_COLOR_BUFFER_BIT);
    this->snake->render();
    this->grid->render();
}