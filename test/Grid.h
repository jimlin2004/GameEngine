#ifndef GRID_H
#define GRID_H

#include "GameEngineAPI/GameEngineAPI.h"
#include "Graphics.h"
#include <vector>
#include <algorithm>

class Grid
{
public:
    Grid();
    void render();
private:
    float sideLength;
    float cellSideLength;
    float midX, midY;
    int cellsNum;
    std::vector<GameEngine::Graphics::Line*> lines;
    GameEngine::Graphics::Point2D leftTopPoint;
    GameEngine::Graphics::Point2D rightBottonPoint;
    void generateLines();
};

#endif