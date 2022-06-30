#include "Arkanoid.h"
#include <SDL.h>

int main(int argc, char* args[]) 
{
    Arkanoid* game = new Arkanoid("Arkanoid", 640, 480);
    bool success = game->Init();
    if (success)
        game->StartGame();
    else
        return 1;
    return 0;
}
