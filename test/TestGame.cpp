#include "TestGame.h"

TestGame::TestGame(const char* title, int width, int height): GameBase(title, width, height)
{
    
}

void TestGame::begin()
{
    this->mainActor = GameEngine::GEngine->spawnActor<MainCharacter>(new GameEngine::Vector(0.f, 0.f, 0.f));
    // GameEngine::GEngine->gameEventManager->bindKeyEvent('w', std::bind(&TestGame::setFlag, this));
    
    // this->rect = new GameEngine::Graphics::Rect(0, 0, 0, 0);
}

void TestGame::setFlag()
{
    printf("Event call\n");
}

void TestGame::gameContext()
{
    glClear(GL_COLOR_BUFFER_BIT);
    this->mainActor->render();
    // this->rect->render();
}