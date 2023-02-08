#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include "GameEngineCore.h"

#include "Grid.h"

class SnakeBody: public GameEngine::Actor
{
public:
    Direction currentDirection;
    Direction nextDirection;
    unsigned int i, j;
    float width, height;
    SnakeBody(float x, float y, float width, float height, unsigned int i, unsigned int j, Direction current);
};

#endif