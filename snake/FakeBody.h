#ifndef FAKEBODY_H
#define FAKEBODY_H

#include "GameEngineCore.h"
#include "Grid.h"

class FakeBody: public GameEngine::Actor
{
public:
    Direction currentDirection;
    float width, height;
    FakeBody(float x, float y, float width, float height, Direction current);
};

#endif