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
public:
    Food(float width, float height);
    void create(Grid& grid);
};

#endif