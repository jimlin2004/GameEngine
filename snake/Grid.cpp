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
    this->data.resize(this->cellsNum + 2, std::vector<GridCell>(this->cellsNum + 2));
    this->initData();
}

void Grid::initData()
{
    float _x = this->leftTopPoint.x - this->cellSideLength;
    float _y = this->rightBottonPoint.y - this->cellSideLength;
    for (int i = 0; i < this->cellsNum + 2; ++i)
    {
        for (int j = 0; j < this->cellsNum + 2; ++j)
        {
            this->data[i][j] = {
                .boundX = _x,
                .boundY = _y,
                .direction = Direction::NONE
            };
            _x += this->cellSideLength;
        }
        _x = this->leftTopPoint.x - this->cellSideLength;
        _y += this->cellSideLength;
    }
    return;
}

void Grid::render()
{
    for (int i = 1; i <= this->cellsNum / 2; ++i)
    {
        GameEngine::Renderer::drawLine({this->midX - (this->cellSideLength * i), this->leftTopPoint.y}, {this->midX - (this->cellSideLength * i), this->rightBottonPoint.y}, {1.0f, 1.0f, 1.0f, 1.0f});
        GameEngine::Renderer::drawLine({this->midX + (this->cellSideLength * i), this->leftTopPoint.y}, {this->midX + (this->cellSideLength * i), this->rightBottonPoint.y}, {1.0f, 1.0f, 1.0f, 1.0f});
        GameEngine::Renderer::drawLine({this->leftTopPoint.x, this->midY - (this->cellSideLength * i)}, {this->rightBottonPoint.x, this->midY - (this->cellSideLength * i)}, {1.0f, 1.0f, 1.0f, 1.0f});
        GameEngine::Renderer::drawLine({this->leftTopPoint.x, this->midY + (this->cellSideLength * i)}, {this->rightBottonPoint.x, this->midY + (this->cellSideLength * i)}, {1.0f, 1.0f, 1.0f, 1.0f});
    }
    GameEngine::Renderer::drawLine({this->midX, this->leftTopPoint.y}, {this->midX, this->rightBottonPoint.y}, {1.0f, 1.0f, 1.0f, 1.0f});
    GameEngine::Renderer::drawLine({this->leftTopPoint.x, this->midY}, {this->rightBottonPoint.x, this->midY}, {1.0f, 1.0f, 1.0f, 1.0f});
}

void Grid::resize()
{
    this->data.resize(this->cellsNum + 2, std::vector<GridCell>(this->cellsNum + 2));
}

void Grid::logData()
{
    for (std::vector<GridCell> vec: this->data)
    {
        for(GridCell cell: vec)
        {
            GameEngine::ConsoleApi::log("%d ", cell.direction);
        }
        GameEngine::ConsoleApi::log("\n");
    }
    GameEngine::ConsoleApi::log("\n");
}