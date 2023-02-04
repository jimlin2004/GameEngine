#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "GameEngineCore.h"
#include "Snake.h"
#include "Grid.h"

class SnakeGame: public GameEngine::GameBase
{
public:
    SnakeGame(const char* title, int width, int height);
    void update(float deltaTime) override;
    void begin() override;
private:
    Snake* snake;
    Grid* grid;
    GameEngine::Texture* testTexture;
    GameEngine::Texture* foodTextureSheet;
    GameEngine::SubTexture* foodTexture;
};

#endif