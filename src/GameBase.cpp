#include "GameBase.h"

GameEngine::GameBase::GameBase(const char* title, int width, int height)
{
    this->title = title;
    this->screenWidth = width;
    this->screenHeight = height;
    this->running = false;
    GameEngine::GEngine->_setWindowSize((float)this->screenWidth, (float)this->screenHeight);
    //bind screen size to PROJECTION_MATRIX
    GameEngine::_currentCamera->setProjectionMatrix(0.0f, (float)this->screenWidth, 0.0f, (float)this->screenHeight);
    // GameEngine::PROJECTION_MATRIX = glm::ortho(0.0f, (float)this->screenWidth, 0.0f, (float)this->screenHeight, -1.0f, 1.0f);
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    this->window = SDL_CreateWindow(this->title, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        this->screenWidth,
        this->screenHeight,
        SDL_WINDOW_OPENGL);
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
    SDL_GL_MakeCurrent(this->window, this->GLContext);
    if (glewInit() != GLEW_OK)
    {
        printf("Init glew error\n");
        return false;
    }
    SDL_GL_SetSwapInterval(1);
    return true;
}

bool GameEngine::GameBase::initGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
                break;
            default:
                break;
        }
    }
}

void GameEngine::GameBase::init()
{
    GameEngine::Renderer::init();
}

void GameEngine::GameBase::begin()
{
    this->init();
    return;
}

void GameEngine::GameBase::startGame()
{
    this->begin();
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