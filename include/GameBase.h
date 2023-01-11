#ifndef GE_GAMEBASE_H
#define GE_GAMEBASE_H

// #include <GL/gl.h>
// #include <GL/glu.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "GameEngineAPI/GameEngineAPI.h"
#include "Graphics.h"
#include "Actor.h"
// #include "GameBaseComponent/GameEventManager/GameEventManager.h"

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
        virtual bool initSDLImage();
        virtual void gameContext();
        void gameEventHandle();
        virtual void begin();
        void startGame();
        //template 需要實現在template裡，不可分
        // template<class TActor, class TGraphics>
        // TActor* spawnActor(TGraphics* graphics)
        // {
        //     TActor* obj = new TActor(graphics->getX(), graphics->getY(), graphics);
        //     return obj;
        // }
    // private:
        // GameEventManager* gameEventManager;
    };
}



#endif