#include "SnakeGame.h"

SnakeGame::SnakeGame(const char* title, int width, int height)
    : GameBase(title, width, height)
{
    
}

void SnakeGame::begin()
{
    this->init();
    this->grid = new Grid(); 
    this->snake = GameEngine::GEngine->spawnActor<Snake>({this->grid->data[20][3].boundX, this->grid->data[20][3].boundY, 0.0f}, {this->grid->getCellSideLength(), this->grid->getCellSideLength()});
    this->snake->setSpeed(this->grid->getCellSideLength());
    this->snake->setBound({this->grid->rightBottonPoint.x, this->grid->rightBottonPoint.y - this->grid->getCellSideLength()});
    // this->grid->data[0][0].direction = Direction::RIGHT;
    this->grid->data[20][1].direction = Direction::RIGHT;
    this->grid->data[20][2].direction = Direction::RIGHT;
    // this->grid->data[20][3].direction = Direction::RIGHT;
    this->food = new Food(this->grid->getCellSideLength(), this->grid->getCellSideLength(), (this->grid->data.size() - 2), (this->grid->data[0].size() - 2));
    return;
}

void SnakeGame::update(float deltaTime)
{
    static bool flag = true;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // this->snake->setSpeed(this->grid->getCellSideLength() * 4 * deltaTime);
    this->snake->setSpeed(0.5f);
    if (this->snake->gameover)
    {
        GameEngine::ConsoleApi::log("Game over\n");
    }
    else
        this->snake->move(*this->grid);
    if (this->snake->ateFood)
    {
        this->snake->ateFood = false;
        this->food->create(*this->grid);
    }
    GameEngine::Renderer::begin();
        this->snake->render();
        this->food->render();
        this->grid->render();
        GameEngine::Renderer::drawQuad({0.0f, 0.0f, -0.1f}, {this->grid->leftTopPoint.x, this->screenHeight}, {0.0f, 0.0f, 0.0f, 1.0f});
        GameEngine::Renderer::drawQuad({this->grid->rightBottonPoint.x, 0.0f, -0.1f}, {this->screenWidth - this->grid->rightBottonPoint.x, this->screenHeight}, {0.0f, 0.0f, 0.0f, 1.0f});
    GameEngine::Renderer::close();
    if (flag)
    {
        flag = false;
        GameEngine::ConsoleApi::log("Quad nums: %u\n", GameEngine::Renderer::getQuadNum());
        GameEngine::ConsoleApi::log("Line nums: %u\n", GameEngine::Renderer::getLineNum());
        GameEngine::ConsoleApi::log("Draw calls: %u\n", GameEngine::Renderer::getDrawCalls());
        this->grid->logData();
    }
}