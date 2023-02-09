#include "Food.h"

Food::Food(float width, float height)
    : GameEngine::Actor(), i(0), j(0)
{
    this->mesh->bindMesh<GameEngine::Graphics::Rect>(width, height);
    this->mesh->setColor({1.0f, 0.0f, 0.0f, 1.0f});
    return;
}

void Food::create(Grid& grid)
{
    srand(time(NULL));
    int _time = 1;
    this->i = GameEngine::randint(1, grid.data.size() - 2);
    this->j = GameEngine::randint(1, grid.data.size() - 2);
    while (grid.data[this->i][this->j].direction != Direction::NONE)
    {
        srand(time(NULL));
        this->i = GameEngine::randint(1, grid.data.size() - 2);
        this->j = GameEngine::randint(1, grid.data.size() - 2);
        _time++;
    }
    this->setPosition(grid.data[this->i][this->j].boundX, grid.data[this->i][this->j].boundY);
    grid.data[this->i][this->j].direction = Direction::FOOD;
    GameEngine::ConsoleApi::log("Rand Time: %d\n", _time);
    return;
}