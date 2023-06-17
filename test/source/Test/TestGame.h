#ifndef TESTGAME_H
#define TESTGAME_H

#include "GameEngineCore.h"

class TestGame: public GameEngine::GameBase
{
public:
    TestGame(const char* title, int width, int height);
    virtual ~TestGame();
    virtual void begin() override;
    virtual void update(float deltaTime) override;
private:
    GameEngine::Actor* testActor;
};

#endif