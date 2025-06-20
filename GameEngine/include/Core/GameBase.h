#ifndef GE_GAMEBASE_H
#define GE_GAMEBASE_H

#include "GL/glew.h"

#include "SDL2/SDL.h"

#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_syswm.h"

#include "box2d/b2_world.h"

#include "Timestep.h"
#include "GameEngineAPI/ConsoleApi.h"
#include "GameEngineAPI/GameEngineAPI.h"
#include "Actor/Actor.h"
#include "Render/Renderer.h"
#include "Scene/SceneSerializer.h"

#define GAMEENGINE_BEGIN() \
            if (GameEngine::GEngine->getEditorSceneFunc() != nullptr) \
                GameEngine::GEngine->getEditorSceneFunc()();

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
        b2World physicsWorld;
        Timestep timestep;
        uint64_t lastFrameTime;
        
        GameBase(const char* title, int width, int height);
        virtual ~GameBase();
        virtual bool initSDL();
        virtual bool initGL();
        virtual void init();
        virtual void update(float deltaTime);
        virtual void render();
        virtual void gameEventHandle();
        virtual void begin();
        virtual void logBuildInfo();
        virtual void startGame();
    };
}

#endif