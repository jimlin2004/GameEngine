#ifndef GRID_H
#define GRID_H

#include "GameEngineCore.h"
#include <vector>
#include <algorithm>

enum Direction
{
    NONE,
    UP, 
    RIGHT, 
    DOWN,
    LEFT 
};

struct GridCell
{
    float boundX, boundY;
    Direction direction;
};

class Grid
{
public:
    GameEngine::Graphics::Point2D leftTopPoint;
    GameEngine::Graphics::Point2D rightBottonPoint;
    std::vector<std::vector<GridCell>> data;
    Grid();
    void render();
    void resize();
    void logData();
    inline float getCellSideLength() const { return cellSideLength; }
private:
    float sideLength;
    float cellSideLength;
    float midX, midY;
    int cellsNum;
    void initData();
};

#endif