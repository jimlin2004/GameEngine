#ifndef TESTGAME_H
#define TESTGAME_H

#include "GameEngineCore.h"

class TestGame: public GameEngine::GameBase
{
public:
    TestGame(const char* title, int width, int height);
    void begin() override;
    void update(float deltaTime) override;
};

#endif