#ifndef TESTGAME_H
#define TESTGAME_H

#include "GameEngineAPI/GameEngineAPI.h"
#include "GameBase.h"
#include "Graphics.h"
#include "MainCharacter.h"

class TestGame: public GameEngine::GameBase
{
public:
    TestGame(const char* title, int width, int height);
    void gameContext() override;
    void begin() override;
    void setFlag();
private:
    // MainCharacter* mainActor;
    GameEngine::Graphics::Rect* rect;
};

#endif