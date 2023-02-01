#include "SnakeGame.h"

SnakeGame::SnakeGame(const char* title, int width, int height): GameBase(title, width, height)
{
    
}

void SnakeGame::begin()
{
    this->init();
    // this->snake = GameEngine::GEngine->spawnActor<Snake>(new GameEngine::Vector(0.f, 0.f, 0.f));
    // this->grid = new Grid();    
    this->testTexture = new GameEngine::Texture();
    this->testTexture->load("../asset/texture/test.png", GL_NEAREST);
}

void SnakeGame::gameContext()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GameEngine::Renderer::begin();
    GameEngine::Renderer::drawQuad({0.0f, 0.0f}, {50.0f, 50.0f}, {0.2f, 0.4f, 0.6f, 1.0f});
    GameEngine::Renderer::drawQuad({50.0f, 0.0f, -0.1f}, {100.0f, 100.0f}, {0.5f, 0.2f, 0.2f, 1.0f});
    // GameEngine::Renderer::drawQuad({50.0f, 0.0f, -0.1f}, {100.0f, 100.0f}, this->testTexture, {0.5f, 0.2f, 0.2f, 1.0f});
    GameEngine::Renderer::close();
    // this->snake->render();
    // this->grid->render();
}