#include "SnakeGame.h"

SnakeGame::SnakeGame(const char* title, int width, int height)
    : GameBase(title, width, height)
{
    
}

void SnakeGame::begin()
{
    this->init();
    this->grid = new Grid(); 
    this->snake = GameEngine::GEngine->spawnActor<Snake>({this->grid->leftTopPoint.x, this->grid->rightBottonPoint.y, 0.0f}, {this->grid->getCellSideLength(), this->grid->getCellSideLength()});
    this->snake->setSpeed(this->grid->getCellSideLength());
}

void SnakeGame::update(float deltaTime)
{
    static bool flag = true;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->snake->setSpeed(0.2f * deltaTime);
    GameEngine::Renderer::begin();
    this->snake->move();
    this->snake->render();
    this->grid->render();
    GameEngine::Renderer::close();
    if (flag)
    {
        flag = false;
        GameEngine::ConsoleApi::log("Quad nums: %u\n", GameEngine::Renderer::getQuadNum());
        GameEngine::ConsoleApi::log("Line nums: %u\n", GameEngine::Renderer::getLineNum());
        GameEngine::ConsoleApi::log("Draw calls: %u\n", GameEngine::Renderer::getDrawCalls());
    }
}