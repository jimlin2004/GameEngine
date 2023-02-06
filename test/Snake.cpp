#include "Snake.h"

Snake::Snake(float x, float y, float width, float height)
    : Character(x, y, width, height), speed(1.0f), direction({1, 0}), previousDirection({1, 0}), origin({x, y})
{
    this->bodys.push_front(new SnakeBody(x, y, width, height, 0, 0));
    this->bodys.push_back(new SnakeBody(x - width, y, width, height, -1, 0));
    this->head = this->bodys.front();
    this->directionType = Direction::RIGHT;
    this->previousDirectionType = Direction::RIGHT;
    this->setInputEvent();
}

void Snake::setInputEvent()
{
    this->playerInputComponent->bindKeyEvent('w', std::bind(&Snake::up, this));
    this->playerInputComponent->bindKeyEvent('a', std::bind(&Snake::left, this));
    this->playerInputComponent->bindKeyEvent('s', std::bind(&Snake::down, this));
    this->playerInputComponent->bindKeyEvent('d', std::bind(&Snake::right, this));
}

void Snake::setSpeed(const float speed)
{
    this->speed = speed;
}

void Snake::setBound(const glm::vec2& bound)
{
    this->bound = bound;
}

void Snake::move(Grid& grid)
{
    this->x += this->previousDirection.x * this->speed;
    this->y += this->previousDirection.y * this->speed;
    GameEngine::ConsoleApi::log("%u %u\n", this->head->j, this->head->i);
    GameEngine::ConsoleApi::log("%f %f\n", this->x, this->y);
    if ((grid.data[this->head->i][this->head->j].boundX < this->x) && (grid.data[this->head->i][this->head->j].boundX + grid.getCellSideLength() > this->x))
    {
        grid.data[this->head->i][this->head->j].direction = this->directionType;
        this->previousDirectionType = this->directionType;
        this->previousDirection = this->direction;
        GameEngine::ConsoleApi::log("%d\n", this->previousDirectionType);
        for (std::vector<GridCell> vec: grid.data)
        {
            for(GridCell cell: vec)
            {
                GameEngine::ConsoleApi::log("%d ", cell.direction);
            }
            GameEngine::ConsoleApi::log("\n");
        }
        GameEngine::ConsoleApi::log("\n");
        this->head->i += this->direction.y;
        this->head->j += this->direction.x;
    }
    else if ((grid.data[this->head->i][this->head->j].boundX > this->x) && (grid.data[this->head->i][this->head->j].boundX - grid.getCellSideLength() < this->x))
    {
        grid.data[this->head->i][this->head->j].direction = this->directionType;
        this->previousDirectionType = this->directionType;
        
        for (std::vector<GridCell> vec: grid.data)
        {
            for(GridCell cell: vec)
            {
                GameEngine::ConsoleApi::log("%d ", cell.direction);
            }
            GameEngine::ConsoleApi::log("\n");
        }
        GameEngine::ConsoleApi::log("\n");
        this->head->i -= this->direction.y;
        this->head->j += this->direction.x;
    }

    if ((grid.data[this->head->i][this->head->j].boundY > this->y) && (grid.data[this->head->i][this->head->j].boundY - grid.getCellSideLength() < this->y) && this->directionType == Direction::DOWN)
    {
        grid.data[this->head->i][this->head->j].direction = this->directionType;
        this->previousDirectionType = this->directionType;
        
        for (std::vector<GridCell> vec: grid.data)
        {
            for(GridCell cell: vec)
            {
                GameEngine::ConsoleApi::log("%d ", cell.direction);
            }
            GameEngine::ConsoleApi::log("\n");
        }
        GameEngine::ConsoleApi::log("\n");
        this->head->i += this->direction.y;
        this->head->j += this->direction.x;
    }
    else if ((grid.data[this->head->i][this->head->j].boundY < this->y) && (grid.data[this->head->i][this->head->j].boundY + grid.getCellSideLength() > this->y) && this->directionType == Direction::UP)
    {
        grid.data[this->head->i][this->head->j].direction = this->directionType;
        this->previousDirectionType = this->directionType;
        
        for (std::vector<GridCell> vec: grid.data)
        {
            for(GridCell cell: vec)
            {
                GameEngine::ConsoleApi::log("%d ", cell.direction);
            }
            GameEngine::ConsoleApi::log("\n");
        }
        GameEngine::ConsoleApi::log("\n");
        this->head->i += this->direction.y;
        this->head->j += this->direction.x;
    }

    for (SnakeBody* body: this->bodys)
    {
        body->setPosition(this->x, this->y);
    }
    if (this->x > this->bound.x)
    {
        this->x = this->origin.x;
        this->head->j = 0;
    }
    else if (this->x < this->origin.x)
    {
        this->x = this->bound.x;
        this->head->j = grid.data.size() - 1;
    }
    if (this->y > this->origin.y)
    {
        this->y = this->bound.y;
        this->head->i = 0;
    }
    else if (this->y < this->bound.y)
    {
        this->y = this->origin.y;
        this->head->i = grid.data.size() - 1;
    }
    return;
}

void Snake::render()
{
    for (SnakeBody* body: this->bodys)
        body->render();
}

void Snake::up()
{
    this->direction = {0, 1};
    this->directionType = Direction::UP;
}

void Snake::left()
{
    this->direction = {-1, 0};
    this->directionType = Direction::LEFT;
}

void Snake::down()
{
    this->direction = {0, -1};
    this->directionType = Direction::DOWN;
}

void Snake::right()
{
    this->direction = {1, 0};
    this->directionType = Direction::RIGHT;
}