#include "SnakeGame.h"

int main(int argc, char* args[])
{
    SnakeGame* game = new SnakeGame("game", 640.0f, 480.0f);
    // bool success = game->initSDL() && game->initGL() && game->initSDLImage();
    bool success = game->initSDL() && game->initGL();
    if (success)
        game->startGame();
    else
        return 1;
    return 0;
}