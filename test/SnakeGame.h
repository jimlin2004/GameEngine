#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "GameEngineAPI/GameEngineAPI.h"
#include "GameBase.h"
#include "Graphics.h"
#include "Renderer.h"
#include "Snake.h"
#include "Grid.h"

class SnakeGame: public GameEngine::GameBase
{
public:
    SnakeGame(const char* title, int width, int height);
    void gameContext() override;
    void begin() override;
private:
    Snake* snake;
    Grid* grid;
};

#endif