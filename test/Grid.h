#ifndef GRID_H
#define GRID_H

#include "GameEngineCore.h"
#include <vector>
#include <algorithm>

class Grid
{
public:
    GameEngine::Graphics::Point2D leftTopPoint;
    GameEngine::Graphics::Point2D rightBottonPoint;
    Grid();
    void render();
    inline float getCellSideLength() const { return cellSideLength; }
private:
    float sideLength;
    float cellSideLength;
    float midX, midY;
    int cellsNum;
};

#endif