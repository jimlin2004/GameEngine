#include "Food.h"

void swapInt(void* a, void* b)
{
    int tmp = *(int*)a;
    *(int*)a = *(int*)b;
    *(int*)b = tmp;
}

Food::Food(float width, float height, int row, int col)
    : GameEngine::Actor(), i(0), j(0), row(row), col(col), lastPosition(row * col - 1)
{
    this->mesh->bindMesh<GameEngine::Graphics::Rect>(width, height);
    this->mesh->setColor({1.0f, 0.0f, 0.0f, 1.0f});
    this->positionTable = new int[row * col];
    for (int i = 0; i < row * col; ++i)
        this->positionTable[i] = i;
    GameEngine::shuffle(this->positionTable, row * col, sizeof(int), &swapInt);
    return;
}

Food::~Food()
{
    delete this->positionTable;
}

void Food::create(Grid& grid)
{
    if (this->row * this->col - this->lastPosition >= 100)
    {
        this->lastPosition = row * col - 1;
        GameEngine::shuffle(this->positionTable, this->row * this->col, sizeof(int), &swapInt);
    }
    this->i = this->positionTable[0] / this->row + 1;
    this->j = this->positionTable[0] % this->row + 1;
    int currentLast = this->lastPosition;
    int _time = 1;
    while (grid.data[this->i][this->j].direction != Direction::NONE)
    {
        swapInt(&this->positionTable[0], &this->positionTable[currentLast]);
        this->i = this->positionTable[0] / this->row + 1;
        this->j = this->positionTable[0] % this->row + 1;
        --currentLast;
        _time++;
    }
    swapInt(&this->positionTable[0], &this->positionTable[this->lastPosition]);
    GameEngine::ConsoleApi::log("Times: %d\n", _time);
    GameEngine::ConsoleApi::log("Last: %d\n", this->lastPosition);
    --this->lastPosition;
    this->setPosition(grid.data[this->i][this->j].boundX, grid.data[this->i][this->j].boundY);
    grid.data[this->i][this->j].direction = Direction::FOOD;
    
}