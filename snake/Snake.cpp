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
    if (grid.data[body->i][grid.data.size() - 2].direction == Direction::RIGHT && (body->x >= grid.data[0][grid.data.size() - 2].boundX))
    {
        if (body == this->tail)
            grid.data[body->i][grid.data.size() - 2].direction = Direction::NONE;
        this->createFakeBody(body->x, body->y, grid.getCellSideLength(), grid.getCellSideLength(), Direction::RIGHT);
        body->x = grid.data[0][0].boundX;
        body->j = 0;
        return true;
    }
    else if (grid.data[body->i][1].direction == Direction::LEFT && (body->x <= grid.data[0][1].boundX))
    {
        if (body == this->tail)
            grid.data[body->i][1].direction = Direction::NONE;
        this->createFakeBody(body->x, body->y, grid.getCellSideLength(), grid.getCellSideLength(), Direction::LEFT);
        body->x = grid.data[0][grid.data.size() - 1].boundX;
        body->j = grid.data.size() - 1;
        return true;
    }
    if (grid.data[grid.data.size() - 2][body->j].direction == Direction::UP && (body->y >= grid.data[grid.data.size() - 2][0].boundY))
    {
        if (body == this->tail)
            grid.data[grid.data.size() - 2][body->j].direction = Direction::NONE;
        this->createFakeBody(body->x, body->y, grid.getCellSideLength(), grid.getCellSideLength(), Direction::UP);
        body->y = grid.data[grid.data.size() - 1][0].boundY;
        body->i = 0;
        return true;
    }
    else if (grid.data[1][body->j].direction == Direction::DOWN && (body->y <= grid.data[1][0].boundY))
    {
        if (body == this->tail)
            grid.data[1][body->j].direction = Direction::NONE;
        this->createFakeBody(body->x, body->y, grid.getCellSideLength(), grid.getCellSideLength(), Direction::DOWN);
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
    //清空fakeBody
    while (!this->fakeBodys.empty())
    {
        this->fakeBodys.pop_front();
    }
    this->fakeBodys.clear();
    this->head->i += this->previousDirection.y;
    this->head->j += this->previousDirection.x;
    
    this->x = grid.data[this->head->i][this->head->j].boundX;
    this->y = grid.data[this->head->i][this->head->j].boundY;
    this->head->setPosition(this->x, this->y);
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
            // grid.data[this->tail->i][this->tail->j].direction = Direction::NONE;
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
            this->tail->currentDirection
        };
    }
    
    grid.data[this->head->i][this->head->j].direction = this->directionType;
    this->previousDirectionType = this->directionType;
    this->previousDirection = this->direction;
    
    glm::vec2 _vec;
    glm::vec2 oldTailIndex = {this->tail->j, this->tail->i};
    bool overed;
    for (std::_List_iterator<SnakeBody*> it = std::next(this->bodys.begin(), 1); it != this->bodys.end(); ++it)
    {
        _vec = this->directionTable[(*it)->currentDirection];
        
        overed = this->overBoundary((*it), grid);
        if (!overed)
        {
            (*it)->i += _vec.y;
            (*it)->j += _vec.x;
            (*it)->currentDirection = grid.data[(*it)->i][(*it)->j].direction;
            this->overBoundary((*it), grid);
        }
        (*it)->x = grid.data[(*it)->i][(*it)->j].boundX;
        (*it)->y = grid.data[(*it)->i][(*it)->j].boundY;
        (*it)->currentDirection = grid.data[(*it)->i][(*it)->j].direction;
        // (*it)->i += _vec.y;
        // (*it)->j += _vec.x;
    }
    
    if (this->growing)
    {
        this->growing = false;
        this->bodys.push_back(new SnakeBody(grid.data[this->newBody.i][this->newBody.j].boundX, grid.data[this->newBody.i][this->newBody.j].boundY, 
            grid.getCellSideLength(), grid.getCellSideLength(), 
            this->newBody.i, this->newBody.j, this->newBody.direction));
        this->tail = this->bodys.back();
        // grid.data[this->tail->i][this->tail->j].direction = Direction::NONE;
    }
    else
        grid.data[oldTailIndex.y][oldTailIndex.x].direction = Direction::NONE;
    this->startFromBoundary = false;
    // GameEngine::ConsoleApi::log("%d\n", this->previousDirectionType);
    // for (std::vector<GridCell> vec: grid.data)
    // {
    //     for(GridCell cell: vec)
    //     {
    //         GameEngine::ConsoleApi::log("%d ", cell.direction);
    //     }
    //     GameEngine::ConsoleApi::log("\n");
    // }
    // GameEngine::ConsoleApi::log("\n");
}

void Snake::move(Grid& grid)
{
    this->x += this->previousDirection.x * this->speed;
    this->y += this->previousDirection.y * this->speed;
    // this->head->setPosition(this->x, this->y);
    // if ((grid.data[this->head->i][this->head->j].boundX + grid.getCellSideLength() <= this->x) && this->previousDirectionType == Direction::RIGHT)
    //     this->moveBodys(grid);
    // else if ((grid.data[this->head->i][this->head->j].boundX - grid.getCellSideLength() >= this->x) && this->previousDirectionType == Direction::LEFT)
    //     this->moveBodys(grid);
    // else if ((grid.data[this->head->i][this->head->j].boundY - grid.getCellSideLength() >= this->y) && this->previousDirectionType == Direction::DOWN)
    //     this->moveBodys(grid);
    // else if ((grid.data[this->head->i][this->head->j].boundY + grid.getCellSideLength() <= this->y) && this->previousDirectionType == Direction::UP)
    //     this->moveBodys(grid);
    if ((grid.data[this->head->i][this->head->j].boundX + grid.getCellSideLength() <= this->head->x) && this->previousDirectionType == Direction::RIGHT)
        this->moveBodys(grid);
    else if ((grid.data[this->head->i][this->head->j].boundX - grid.getCellSideLength() >= this->head->x) && this->previousDirectionType == Direction::LEFT)
        this->moveBodys(grid);
    else if ((grid.data[this->head->i][this->head->j].boundY - grid.getCellSideLength() >= this->head->y) && this->previousDirectionType == Direction::DOWN)
        this->moveBodys(grid);
    else if ((grid.data[this->head->i][this->head->j].boundY + grid.getCellSideLength() <= this->head->y) && this->previousDirectionType == Direction::UP)
        this->moveBodys(grid);
    if (this->previousDirectionType == Direction::RIGHT && (this->head->x >= grid.data[0][grid.data.size() - 2].boundX))
    {
        this->createFakeBody(this->x, this->y, grid.getCellSideLength(), grid.getCellSideLength(), Direction::RIGHT);
        this->x = grid.data[0][0].boundX;
        grid.data[this->head->i][0].direction = Direction::RIGHT;
        this->head->j = 0;
        this->startFromBoundary = true;
        
    }
    else if (this->previousDirectionType == Direction::LEFT && (this->head->x <= grid.data[0][1].boundX))
    {
        this->createFakeBody(this->head->x, this->head->y, grid.getCellSideLength(), grid.getCellSideLength(), Direction::LEFT);
        this->x = grid.data[0][grid.data.size() - 1].boundX;
        // grid.data[this->head->i][1].direction = this->previousDirectionType;
        grid.data[this->head->i][grid.data.size() - 1].direction = Direction::LEFT;
        this->head->j = grid.data.size() - 1;
        this->startFromBoundary = true;
    }
    if (this->previousDirectionType == Direction::UP && (this->head->y >= grid.data[grid.data.size() - 2][0].boundY))
    {
        this->createFakeBody(this->x, this->y, grid.getCellSideLength(), grid.getCellSideLength(), Direction::UP);
        this->y = grid.data[0][0].boundY;
        // grid.data[grid.data.size() - 2][this->head->j].direction = this->previousDirectionType;
        grid.data[0][this->head->j].direction = Direction::UP;
        this->head->i = 0;
        this->startFromBoundary = true;
    }
    else if (this->previousDirectionType == Direction::DOWN && (this->head->y <= grid.data[1][0].boundY))
    {
        this->createFakeBody(this->x, this->y, grid.getCellSideLength(), grid.getCellSideLength(), Direction::DOWN);
        this->y = grid.data[grid.data.size() - 1][0].boundY;
        // grid.data[1][this->head->j].direction = this->previousDirectionType;
        grid.data[grid.data.size() - 1][this->head->j].direction = Direction::DOWN;
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
    //移動fake body
    for (std::_List_iterator<FakeBody*> it = this->fakeBodys.begin(); it != this->fakeBodys.end(); ++it)
    {
        _vec = this->directionTable[(*it)->currentDirection];
        _x = (*it)->x + (_vec.x * this->speed);
        _y = (*it)->y + (_vec.y * this->speed);
        (*it)->setPosition(_x, _y);
    }
}

void Snake::createFakeBody(float x, float y, float width, float height, Direction current)
{
    this->fakeBodys.push_back(new FakeBody(x, y, width, height, current));
}

void Snake::render()
{
    // this->food->render();
    for (SnakeBody* body: this->bodys)
        body->render();
    for (FakeBody* body: this->fakeBodys)
        body->render();
}

void Snake::up()
{
    if (this->previousDirectionType == Direction::DOWN)
        return;
    this->direction = {0, 1};
    this->directionType = Direction::UP;
}

void Snake::left()
{
    if (this->previousDirectionType == Direction::RIGHT)
        return;
    this->direction = {-1, 0};
    this->directionType = Direction::LEFT;
}

void Snake::down()
{
    if (this->previousDirectionType == Direction::UP)
        return;
    this->direction = {0, -1};
    this->directionType = Direction::DOWN;
}

void Snake::right()
{
    if (this->previousDirectionType == Direction::LEFT)
        return;
    this->direction = {1, 0};
    this->directionType = Direction::RIGHT;
}