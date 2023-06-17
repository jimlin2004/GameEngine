#include "TestGame.h"

TestGame::TestGame(const char* title, int width, int height)
    : GameEngine::GameBase(title, width, height)
{
}

TestGame::~TestGame()
{
}

void TestGame::begin()
{
    GAMEENGINE_BEGIN()

    this->testActor = GameEngine::globalScene->spawnActor<GameEngine::Actor>({100.0f, 100.0f, 1.0f}, {50.0f, 50.0f, 1.0f}, {0.0f, 0.0f, 0.5f});
}

void TestGame::update(float deltaTime)
{
    
}