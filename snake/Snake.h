#ifndef SNAKE_H
#define SNAKE_H

#include "GameEngineCore.h"

#include "Grid.h"
#include "SnakeBody.h"
#include "FakeBody.h"
#include "Food.h"
#include <array>
#include <list>

struct NewBody
{
    unsigned int i, j;
    Direction direction;
};

class Snake: public GameEngine::Character
{
public:
    bool ateFood;
    bool gameover;
    
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
    std::array<const glm::vec2, 5> directionTable;
    glm::vec2 previousDirection;
    Direction previousDirectionType;
    std::list<SnakeBody*> bodys;
    std::list<FakeBody*> fakeBodys;
    SnakeBody* head;
    SnakeBody* tail;
    bool growing;
    bool startFromBoundary;
    NewBody newBody;

    // void clearTail(Grid& grid);
    bool overBoundary(SnakeBody* body, Grid& grid);
    void moveBodys(Grid& grid);
    Direction getOppositeDirection(Direction _direction);
    void createFakeBody(float x, float y, float width, float height, Direction current);
};

#endif