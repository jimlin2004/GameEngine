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
    static bool flag = true;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GameEngine::Renderer::begin();
    // GameEngine::Renderer::drawQuad({0.0f, 0.0f}, {50.0f, 50.0f}, {0.2f, 0.4f, 0.6f, 1.0f});
    // GameEngine::Renderer::drawRotatedQuad({35.3553f, 85.3553f}, {50.0f, 50.0f}, 45.0f, {0.2f, 0.4f, 0.6f, 1.0f});
    // GameEngine::Renderer::drawQuad({30.0f, 0.0f, -0.1f}, {50.0f, 50.0f}, this->testTexture, {0.5f, 0.2f, 0.2f, 1.0f});
    // GameEngine::Renderer::drawRotatedQuad({0.0f, 0.0f, 0.1f}, {50.0f, 50.0f}, 45.0f, this->testTexture, {0.5f, 0.2f, 0.2f, 1.0f});
    for (int i = 0; i < 10000; ++i)
    {
        GameEngine::Renderer::drawQuad({10.0f * (i % 100), 10.0f * (i / 100), 0.0f}, {8.0f, 8.0f}, {0.2f, 0.4f, 0.6f, 1.0f});
    }
    GameEngine::Renderer::close();
    // this->snake->render();
    // this->grid->render();
    if (flag)
    {
        flag = false;
        GameEngine::ConsoleApi::log("Quad nums: %u\n", GameEngine::Renderer::getQuadNum());
        GameEngine::ConsoleApi::log("Draw calls: %u\n", GameEngine::Renderer::getDrawCalls());
    }
}