#ifndef MAINCHARACTER
#define MAINCHARACTER

#include "Actor.h"
#include "Graphics.h"

class MainCharacter: public GameEngine::Character
{
public:
    MainCharacter(float x, float y);
    void setInputEvent() override;
    void test();
};

#endif