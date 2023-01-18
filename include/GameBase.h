#ifndef GE_GAMEBASE_H
#define GE_GAMEBASE_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

#include "GameEngineAPI/GameEngineAPI.h"
#include "Graphics.h"
#include "Actor.h"

namespace GameEngine
{
    enum class GameState
    {
        ACTIVE,
        WIN,
        QUIT
    };

    class GameBase
    {
    public:
        int screenWidth;
        int screenHeight;
        const char* title;
        bool running;
        SDL_Event event;
        SDL_Window* window;
        SDL_GLContext GLContext;

        GameBase(const char* title, int width, int height);
        ~GameBase();
        virtual bool initSDL();
        virtual bool initGL();
        virtual void gameContext();
        void gameEventHandle();
        virtual void begin();
        void startGame();
    };
}

#endif