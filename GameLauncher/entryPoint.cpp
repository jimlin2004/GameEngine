#include "GameLauncher.h"

int main(int argc, char* argv[])
{
    GameLauncher* launcher = new GameLauncher("test", 640, 480);
    bool ok = launcher->initAll();
    if (ok)
        launcher->startGame();
    return 0;
}