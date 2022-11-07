#include "GameBase.h"

GameEngine::GameBase::GameBase(const char* title, int width, int height)
{
    this->title = title;
    this->screenWidth = width;
    this->screenHeight = height;
    this->running = false;
    // this->gameEventManager = new GameEventManager();
}

GameEngine::GameBase::~GameBase()
{
    return;
}

bool GameEngine::GameBase::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL Init Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    this->window = SDL_CreateWindow(this->title, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        this->screenWidth,
        this->screenHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!this->window)
    {
        printf("Create Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    this->GLContext = SDL_GL_CreateContext(this->window);
    if (!this->GLContext)
    {
        printf("Create Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    SDL_GL_SetSwapInterval(1);
    return true;
}

bool GameEngine::GameBase::initGL()
{
    // float ratio = (float)(this->screenWidth / this->screenHeight);    
    // glShadeModel(GL_SMOOTH);  
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(this->window);

    // Setup our viewport.  
    // glViewport(0, 0, this->screenWidth, this->screenHeight);    
    glMatrixMode(GL_PROJECTION); //投影矩陣
    glLoadIdentity(); //單位矩陣
    // gluPerspective(60.0, ratio, 1.0, 100.0);
    glOrtho(0.0f, this->screenWidth, this->screenHeight, 0.0f, -1.0f, 1.0f);
    return true;
}

void GameEngine::GameBase::gameContext()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void GameEngine::GameBase::gameEventHandle()
{
    while (SDL_PollEvent(&this->event))
    {
        switch (this->event.type)
        {
            case SDL_QUIT:
                this->running = false;
                break;
            case SDL_KEYDOWN:
                GameEngine::GEngine->callKeyEvent(this->event.key.keysym.sym);
                // this->gameEventManager->callKeyEvent(this->event.key.keysym.sym);
                // switch (this->event.key.keysym.sym)
                // {
                //     case 'w':
                //         printf("hi\n");
                //         break;
                //     default:
                //         break;
                // }
                break;
            default:
                break;
        }
    }
}

void GameEngine::GameBase::startGame()
{
    // this->gameEventManager = new GameEventManager();
    // this->gameEventManager->bindKeyEvent('w', [](){ printf("Test\n"); });
    // this->gameEventManager->bindKeyEvent('w', std::bind(&this->))
    this->running = true;
    while (this->running)
    {
        this->gameEventHandle();
        this->gameContext();
        SDL_GL_SwapWindow(this->window);
    }
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}