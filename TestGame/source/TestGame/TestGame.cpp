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
    this->testActor = GameEngine::globalScene->spawnActor<TestActor>({300.0f, 300.0f, 1.0f}, {50.0f, 50.0f, 1.0f}, {0.0f, 0.0f, 45.0f}, "TestActor");
    GameEngine::Texture* texture = new GameEngine::Texture();
    texture->load("D:/code/cpp/gameEngine/build/TestGame/assets/texture/test.png", GL_LINEAR);
    this->testActor->getComponent<GameEngine::MeshComponent>().texture = texture;
    GameEngine::globalScene->spawnActor<TestActor>({400.0f, 300.0f, 1.0f}, {50.0f, 50.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, "TestActor2");
}

void TestGame::update(float deltaTime)
{
}