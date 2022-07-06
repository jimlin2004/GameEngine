#include "Arkanoid.h"
#include <SDL.h>

int main(int argc, char* args[]) 
{
    Arkanoid* game = new Arkanoid("Arkanoid", 640, 480);
    bool success = game->init();
    if (success)
        game->startGame();
    else
        return 1;
    return 0;
}
