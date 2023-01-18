#include "Grid.h"

Grid::Grid()
{
    this->cellsNum = 20;
    this->sideLength = std::min(GameEngine::GEngine->getWindowWidth(), GameEngine::GEngine->getWindowHeight());
    this->cellSideLength = this->sideLength / this->cellsNum;
    this->midX = GameEngine::GEngine->getWindowWidth() / 2;
    this->midY = GameEngine::GEngine->getWindowHeight() / 2;
    this->leftTopPoint = {
        .x = this->midX - (this->cellSideLength * this->cellsNum / 2),
        .y = this->midY + (this->cellSideLength * this->cellsNum / 2),
    };
    this->rightBottonPoint = {
        .x = this->midX + (this->cellSideLength * this->cellsNum / 2),
        .y = this->midY - (this->cellSideLength * this->cellsNum / 2),
    };
    this->generateLines();
}

void Grid::generateLines()
{
    for (int i = 1; i <= this->cellsNum / 2; ++i)
    {
        this->lines.push_back(new GameEngine::Graphics::Line(this->midX - (this->cellSideLength * i), this->leftTopPoint.y, this->midX - (this->cellSideLength * i), this->rightBottonPoint.y));
        this->lines.push_back(new GameEngine::Graphics::Line(this->midX + (this->cellSideLength * i), this->leftTopPoint.y, this->midX + (this->cellSideLength * i), this->rightBottonPoint.y));
        this->lines.push_back(new GameEngine::Graphics::Line(this->leftTopPoint.x, this->midY - (this->cellSideLength * i), this->rightBottonPoint.x, this->midY - (this->cellSideLength * i)));
        this->lines.push_back(new GameEngine::Graphics::Line(this->leftTopPoint.x, this->midY + (this->cellSideLength * i), this->rightBottonPoint.x, this->midY + (this->cellSideLength * i)));
    }
    this->lines.push_back(new GameEngine::Graphics::Line(this->midX, this->leftTopPoint.y, this->midX, this->rightBottonPoint.y));
    this->lines.push_back(new GameEngine::Graphics::Line(this->leftTopPoint.x, midY, this->rightBottonPoint.x, midY));
}

void Grid::render()
{
    for (GameEngine::Graphics::Line* line: this->lines)
    {
        line->render();
    }
}