#ifndef GAME_LAUNCHER_H
#define GAME_LAUNCHER_H

#include "Core/GameBase.h"

class GameLauncher: public GameEngine::GameBase
{
public:
    GameLauncher(const char* title, int width, int height);

    bool initAll();

    
};

#endif