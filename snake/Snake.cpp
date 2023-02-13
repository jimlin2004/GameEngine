#include "Snake.h"

Snake::Snake(float x, float y, float width, float height)
    : Character(x, y, width, height), speed(1.0f), direction({1, 0}), previousDirection({1, 0}), origin({x, y})
    , directionTable({glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 0), glm::vec2(0, -1), glm::vec2(-1, 0)})
    , ateFood(true), growing(false), gameover(false), startFromBoundary(false)
{
    this->bodys.push_front(new SnakeBody(x, y, width, height, 20, 3, Direction::RIGHT));
    this->bodys.push_back(new SnakeBody(x - width, y, width, height, 20, 2, Direction::RIGHT));
    this->bodys.push_back(new SnakeBody(x - width - width, y, width, height, 20, 1, Direction::RIGHT));
    this->head = this->bodys.front();
    this->tail = this->bodys.back();
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

Direction Snake::getOppositeDirection(Direction _direction)
{
    switch (_direction)
    {
        case Direction::RIGHT: return Direction::LEFT;
        case Direction::LEFT: return Direction::RIGHT;
        case Direction::DOWN: return Direction::UP;
        case Direction::UP: return Direction::DOWN;
        default: return Direction::NONE;
    }
}

bool Snake::overBoundary(SnakeBody* body, Grid& grid)
{
    if (body->currentDirection == Direction::RIGHT && (body->x >= grid.data[0][grid.data.size() - 2].boundX))
    {
        body->x = grid.data[0][0].boundX;
        body->j = 0;
        return true;
    }
    else if (body->currentDirection == Direction::LEFT && (body->x <= grid.data[0][1].boundX))
    {
        body->x = grid.data[0][grid.data.size() - 1].boundX;
        body->j = grid.data.size() - 1;
        return true;
    }
    if (body->currentDirection == Direction::UP && (body->y >= grid.data[grid.data.size() - 2][0].boundY))
    {
        body->y = grid.data[grid.data.size() - 1][0].boundY;
        body->i = 0;
        return true;
    }
    else if (body->currentDirection == Direction::DOWN && (body->y <= grid.data[1][0].boundY))
    {
        body->y = grid.data[21][0].boundY;
        body->i = grid.data.size() - 1;
        return true;
    }
    return false;
}

void Snake::moveBodys(Grid& grid)
{
    static bool firstTime = true;
    if (firstTime)
    {
        firstTime = false;
        return;
    }
    if (grid.data[this->head->i][this->head->j].direction == Direction::FOOD)
    {
        this->ateFood = true;
        this->growing = true;
    }
    else if (grid.data[this->head->i][this->head->j].direction != Direction::NONE)
    {
        if (this->startFromBoundary)
        {
            this->startFromBoundary = false;
            grid.data[this->tail->i][this->tail->j].direction = Direction::NONE;
        }
            
        else
            this->gameover = true;
    }
    // else
        // grid.data[this->tail->i][this->tail->j].direction = Direction::NONE;
    if (this->ateFood)
    {
        // this->ateFood = false;
        // this->food->create(grid);
        this->newBody = {
            this->tail->i, this->tail->j, 
            grid.data[this->tail->i][this->tail->j].direction
        };
    }
    grid.data[this->head->i][this->head->j].direction = this->directionType;
    this->previousDirectionType = this->directionType;
    this->previousDirection = this->direction;
    
    this->head->i += this->direction.y;
    this->head->j += this->direction.x;
    this->x = grid.data[this->head->i][this->head->j].boundX;
    this->y = grid.data[this->head->i][this->head->j].boundY;
    // this->head->i += this->direction.y;
    // this->head->j += this->direction.x;
    this->head->setPosition(this->x, this->y);
    glm::vec2 _vec;
    glm::vec2 oldTailIndex = {this->tail->j, this->tail->i};
    bool overed;
    for (std::_List_iterator<SnakeBody*> it = std::next(this->bodys.begin(), 1); it != this->bodys.end(); ++it)
    {
        (*it)->currentDirection = grid.data[(*it)->i][(*it)->j].direction;
        _vec = this->directionTable[(*it)->currentDirection];
        overed = this->overBoundary((*it), grid);
        if (!overed)
        {
            (*it)->i += _vec.y;
            (*it)->j += _vec.x;
        }
        (*it)->x = grid.data[(*it)->i][(*it)->j].boundX;
        (*it)->y = grid.data[(*it)->i][(*it)->j].boundY;
        // (*it)->i += _vec.y;
        // (*it)->j += _vec.x;
    }
    grid.data[oldTailIndex.y][oldTailIndex.x].direction = Direction::NONE;
    if (this->growing)
    {
        this->growing = false;
        this->bodys.push_back(new SnakeBody(grid.data[this->newBody.i][this->newBody.j].boundX, grid.data[this->newBody.i][this->newBody.j].boundY, 
            grid.getCellSideLength(), grid.getCellSideLength(), 
            this->newBody.i, this->newBody.j, this->newBody.direction));
        this->tail = this->bodys.back();
    }
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
}

void Snake::move(Grid& grid)
{
    this->x += this->previousDirection.x * this->speed;
    this->y += this->previousDirection.y * this->speed;
    
    // if ((grid.data[this->head->i][this->head->j].boundX < this->x) && (grid.data[this->head->i][this->head->j].boundX + grid.getCellSideLength() > this->x) && this->previousDirectionType == Direction::RIGHT)
    //     this->moveBodys(grid);
    // else if ((grid.data[this->head->i][this->head->j].boundX > this->x) && (grid.data[this->head->i][this->head->j].boundX - grid.getCellSideLength() < this->x) && this->previousDirectionType == Direction::LEFT)
    //     this->moveBodys(grid);
    // else if ((grid.data[this->head->i][this->head->j].boundY > this->y) && (grid.data[this->head->i][this->head->j].boundY - grid.getCellSideLength() < this->y) && this->previousDirectionType == Direction::DOWN)
    //     this->moveBodys(grid);
    // else if ((grid.data[this->head->i][this->head->j].boundY < this->y) && (grid.data[this->head->i][this->head->j].boundY + grid.getCellSideLength() > this->y) && this->previousDirectionType == Direction::UP)
    //     this->moveBodys(grid);
    
    // float _x, _y;
    // glm::vec2 _vec;
    this->head->setPosition(this->x, this->y);
    // for (std::_List_iterator<SnakeBody*> it = std::next(this->bodys.begin(), 1); it != this->bodys.end(); ++it)
    // {
    //     _vec = this->directionTable[(*it)->currentDirection];
    //     _x = (*it)->x + (_vec.x * this->speed);
    //     _y = (*it)->y + (_vec.y * this->speed);
    //     (*it)->setPosition(_x, _y);
    // }

    if (this->previousDirectionType == Direction::RIGHT && (this->x >= grid.data[0][grid.data.size() - 2].boundX))
    {
        this->x = grid.data[0][0].boundX;
        grid.data[this->head->i][grid.data.size() - 2].direction = this->previousDirectionType;
        this->head->j = 0;
        this->startFromBoundary = true;
    }
    else if (this->previousDirectionType == Direction::LEFT && (this->x <= grid.data[0][1].boundX))
    {
        this->x = grid.data[0][grid.data.size() - 1].boundY;
        grid.data[this->head->i][1].direction = this->previousDirectionType;
        this->head->j = grid.data.size() - 1;
        this->startFromBoundary = true;
    }
    if (this->previousDirectionType == Direction::UP && (this->y >= grid.data[grid.data.size() - 2][0].boundY))
    {
        this->y = grid.data[0][0].boundY;
        grid.data[grid.data.size() - 2][this->head->j].direction = this->previousDirectionType;
        this->head->i = 0;
        this->startFromBoundary = true;
    }
    else if (this->previousDirectionType == Direction::DOWN && (this->y <= grid.data[1][0].boundY))
    {
        this->y = grid.data[grid.data.size() - 1][0].boundY;
        grid.data[1][this->head->j].direction = this->previousDirectionType;
        this->head->i = grid.data.size() - 1;
        this->startFromBoundary = true;
    }

    float _x, _y;
    glm::vec2 _vec;
    this->head->setPosition(this->x, this->y);
    for (std::_List_iterator<SnakeBody*> it = std::next(this->bodys.begin(), 1); it != this->bodys.end(); ++it)
    {
        _vec = this->directionTable[(*it)->currentDirection];
        _x = (*it)->x + (_vec.x * this->speed);
        _y = (*it)->y + (_vec.y * this->speed);
        (*it)->setPosition(_x, _y);
    }

    if ((grid.data[this->head->i][this->head->j].boundX + grid.getCellSideLength() <= this->x) && this->previousDirectionType == Direction::RIGHT)
        this->moveBodys(grid);
    else if ((grid.data[this->head->i][this->head->j].boundX - grid.getCellSideLength() >= this->x) && this->previousDirectionType == Direction::LEFT)
        this->moveBodys(grid);
    else if ((grid.data[this->head->i][this->head->j].boundY - grid.getCellSideLength() >= this->y) && this->previousDirectionType == Direction::DOWN)
        this->moveBodys(grid);
    else if ((grid.data[this->head->i][this->head->j].boundY + grid.getCellSideLength() <= this->y) && this->previousDirectionType == Direction::UP)
        this->moveBodys(grid);
    // if ((grid.data[this->head->i][this->head->j].boundX < this->x) && (grid.data[this->head->i][this->head->j].boundX + grid.getCellSideLength() > this->x) && this->previousDirectionType == Direction::RIGHT)
    //     this->moveBodys(grid);
    // else if ((grid.data[this->head->i][this->head->j].boundX > this->x) && (grid.data[this->head->i][this->head->j].boundX - grid.getCellSideLength() < this->x) && this->previousDirectionType == Direction::LEFT)
    //     this->moveBodys(grid);
    // else if ((grid.data[this->head->i][this->head->j].boundY > this->y) && (grid.data[this->head->i][this->head->j].boundY - grid.getCellSideLength() < this->y) && this->previousDirectionType == Direction::DOWN)
    //     this->moveBodys(grid);
    // else if ((grid.data[this->head->i][this->head->j].boundY < this->y) && (grid.data[this->head->i][this->head->j].boundY + grid.getCellSideLength() > this->y) && this->previousDirectionType == Direction::UP)
    //     this->moveBodys(grid);
}

void Snake::render()
{
    // this->food->render();
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