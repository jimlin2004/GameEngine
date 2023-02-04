#ifndef SNAKE_H
#define SNAKE_H

#include "GameEngineCore.h"

class Snake: public GameEngine::Character
{
public:
    Snake(float x, float y, float width, float height);
    void setInputEvent() override;
    void setSpeed(float speed);
    void up();
    void left();
    void down();
    void right();
    void move();
private:
    float speed;
    glm::vec2 direction;
};

#endif