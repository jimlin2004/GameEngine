#include "GameLauncher.h"

GameLauncher::GameLauncher(const char * title, int width, int height)
    : GameEngine::GameBase(title, width, height)
{
}

bool GameLauncher::initAll()
{
    bool result = this->initSDL() && this->initGL();
    if (!result)
        return false;
    this->init();
    return true;
}
