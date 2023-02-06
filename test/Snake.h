#ifndef SNAKE_H
#define SNAKE_H

#include "GameEngineCore.h"

#include "Grid.h"
#include "SnakeBody.h"
#include <list>

class Snake: public GameEngine::Character
{
public:
    Snake(float x, float y, float width, float height);
    void setInputEvent() override;
    void setSpeed(const float speed);
    void setBound(const glm::vec2& bound);
    void up();
    void left();
    void down();
    void right();
    void move(Grid& grid);
    void render() override;
private:
    float speed;
    glm::vec2 origin;
    glm::vec2 bound;
    glm::vec2 direction;
    Direction directionType;
    glm::vec2 previousDirection;
    Direction previousDirectionType;
    std::list<SnakeBody*> bodys;
    SnakeBody* head;
};

#endif