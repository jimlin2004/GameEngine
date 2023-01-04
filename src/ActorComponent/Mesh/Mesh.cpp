#include "../include/ActorComponent/Mesh/Mesh.h"

GameEngine::Mesh::Mesh()
{
    this->graphics = nullptr;
    this->rootX = this->rootY = nullptr;
    return;
}

GameEngine::Mesh::Mesh(float* rootX, float* rootY)
{
    this->graphics = nullptr;
    this->rootX = rootX;
    this->rootY = rootY;
    return;
}

GameEngine::Mesh::Mesh(float* rootX, float* rootY, GameEngine::Graphics::Graphics* graphics)
{
    this->rootX = rootX;
    this->rootY = rootY;
    this->graphics = graphics;
    return;
}

GameEngine::Mesh::~Mesh()
{
    delete this->graphics;
    delete this->rootX;
    delete this->rootY;
    return;
}

void GameEngine::Mesh::bindMesh(GameEngine::Graphics::Graphics* graphics)
{
    this->graphics = graphics;
}

void GameEngine::Mesh::render()
{
    this->graphics->render();
}