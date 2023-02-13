#ifndef FOOD_H
#define FOOD_H

#include "GameEngineCore.h"

#include <time.h>
#include <stdlib.h>

#include "Grid.h"

class Food: public GameEngine::Actor
{
private:
    unsigned int i;
    unsigned int j;
    int* positionTable;
    unsigned int row;
    unsigned int col;
    unsigned int lastPosition;
public:
    Food(float width, float height, int row, int col);
    ~Food();
    void create(Grid& grid);
};

#endif