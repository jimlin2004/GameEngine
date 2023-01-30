#include "SnakeGame.h"

SnakeGame::SnakeGame(const char* title, int width, int height): GameBase(title, width, height)
{
    
}

void SnakeGame::begin()
{
    this->init();
    // this->snake = GameEngine::GEngine->spawnActor<Snake>(new GameEngine::Vector(0.f, 0.f, 0.f));
    // this->grid = new Grid();
}

void SnakeGame::gameContext()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GameEngine::Renderer::begin();
    GameEngine::Renderer::drawQuad({0.0f, 0.0f}, {50.0f, 50.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
    GameEngine::Renderer::close();
    // this->snake->render();
    // this->grid->render();
}