#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "GameEngineCore.h"
#include "Snake.h"
#include "Grid.h"
#include "Food.h"

class SnakeGame: public GameEngine::GameBase
{
public:
    SnakeGame(const char* title, int width, int height);
    void update(float deltaTime) override;
    void begin() override;
private:
    Grid* grid;
    Snake* snake;
    Food* food;
};

#endif