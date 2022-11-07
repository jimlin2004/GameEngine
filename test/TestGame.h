#ifndef TESTGAME_H
#define TESTGAME_H

#include "GameEngineAPI/GameEngineAPI.h"
#include "GameBase.h"
#include "Actor.h"

class TestGame: public GameEngine::GameBase
{
public:
    TestGame(const char* title, int width, int height);
    void gameContext() override;
    void setFlag();
private:
    GameEngine::Character* mainActor;
};

#endif