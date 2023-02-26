#ifndef TESTGAME_H
#define TESTGAME_H

#include "GameEngineCore.h"

class TestGame: public GameEngine::GameBase
{
public:
    TestGame(const char* title, int width, int height);
    void update(float deltaTime) override;
    void begin() override;
};

#endif