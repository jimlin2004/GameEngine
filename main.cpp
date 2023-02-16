#include "GameBase.h"

int main(int argc, char* args[])
{
    GameEngine::GameBase* game = new GameEngine::GameBase("game", 640, 480);
    bool success = game->initSDL() && game->initGL();
    if (success)
        game->startGame();
    else
        return 1;
    return 0;
}