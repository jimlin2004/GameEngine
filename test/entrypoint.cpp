#include "TestGame.h"

int main(int argc, char* args[])
{
    TestGame* game = new TestGame("game", 640.0f, 480.0f);
    // bool success = game->initSDL() && game->initGL() && game->initSDLImage();
    bool success = game->initSDL() && game->initGL();
    if (success)
        game->startGame();
    else
        return 1;
    return 0;
}