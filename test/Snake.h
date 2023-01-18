#ifndef SNAKE_H
#define SNAKE_H

#include "Actor.h"
#include "Graphics.h"

class Snake: public GameEngine::Character
{
public:
    Snake(float x, float y);
    void setInputEvent() override;
    void up();
    void left();
    void down();
    void right();
};

#endif