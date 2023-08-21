#include "Core/GameBase.h"

int main(int argc, char* args[])
{
    GameEngine::GameBase* game = new GameEngine::GameBase("TestGame", 640.0f, 480.0f);
    bool success = game->initSDL() && game->initGL();
    if (success)
        game->startGame();
    else
        return 1;
    return 0;
}