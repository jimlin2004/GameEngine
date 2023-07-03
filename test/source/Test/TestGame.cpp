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
}

void TestGame::update(float deltaTime)
{
    
}