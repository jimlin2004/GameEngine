#ifndef GE_GAMEBASE_H
#define GE_GAMEBASE_H

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "box2d/b2_world.h"

#include "Timestep.h"
#include "GameEngineAPI/ConsoleApi.h"
#include "GameEngineAPI/GameEngineAPI.h"
#include "Graphics.h"
#include "Actor.h"
#include "Renderer.h"

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
        void init();
        virtual void update(float deltaTime);
        void gameEventHandle();
        virtual void begin();
        virtual void logBuildInfo();
        void startGame();
    private:
        b2World physicsWorld;
        Timestep timestep;
        uint64_t lastFrameTime;
    };
}

#endif