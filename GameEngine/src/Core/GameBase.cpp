#include "Core/GameBase.h"
#include "Core/CameraController.h"
#include "Event/Input.h"

GameEngine::GameBase::GameBase(const char* title, int width, int height)
    : title(title)
    , screenWidth(width)
    , screenHeight(height)
    , running(false)
    , physicsWorld({0.0f, -9.8f})
{
    this->lastFrameTime = 0.0f;
    GameEngine::GEngine->_setWindowSize((float)this->screenWidth, (float)this->screenHeight);
    //bind screen size to PROJECTION_MATRIX
    GameEngine::cameraController->getCamera()->setProjection(0.0f, (float)this->screenWidth, 0.0f, (float)this->screenHeight);
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
        GameEngine::ConsoleApi::log("[Error] SDL Init Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    this->window = SDL_CreateWindow(this->title, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        this->screenWidth,
        this->screenHeight,
        SDL_WINDOW_OPENGL);
    if (!this->window)
    {
        GameEngine::ConsoleApi::log("[Error] Create Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    
    this->GLContext = SDL_GL_CreateContext(this->window);
    if (!this->GLContext)
    {
        GameEngine::ConsoleApi::log("[Error] Create Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    GameEngine::ConsoleApi::log("[Info] Create windows success.\n");
    SDL_GL_MakeCurrent(this->window, this->GLContext);
    if (glewInit() != GLEW_OK)
    {
        GameEngine::ConsoleApi::log("Init glew error\n");
        return false;
    }
    GameEngine::ConsoleApi::log("[Info] OpenGL init success.\n");
    SDL_GL_SetSwapInterval(1);
    return true;
}

bool GameEngine::GameBase::initGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    return true;
}

void GameEngine::GameBase::update(float deltaTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    GAMEENGINE_BEGIN();
}

void GameEngine::GameBase::logBuildInfo()
{
    GameEngine::ConsoleApi::log("[Info] Game running success.\n");
    GameEngine::ConsoleApi::log("\n==============================================\n");
    GameEngine::ConsoleApi::log("[Info] Build Infomation\n");
    GameEngine::ConsoleApi::log("Opengl version: %s\n", glGetString(GL_VERSION));
    GameEngine::ConsoleApi::log("==============================================\n\n");
    fflush(stdout);
}

void GameEngine::GameBase::render()
{
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Renderer::begin();
    //     GameEngine::globalScene->render();
    // Renderer::close();
}

void GameEngine::GameBase::startGame()
{
    this->init();
    this->begin();
    this->logBuildInfo();
    this->running = true;
    uint64_t time = SDL_GetPerformanceCounter();
    while (this->running)
    {
        this->lastFrameTime = time;
        time = SDL_GetPerformanceCounter();
        this->timestep = ((time - this->lastFrameTime) * 1000.0f / SDL_GetPerformanceFrequency()) * 0.001f;
        this->gameEventHandle();
        this->update(this->timestep);
        //Todo
        // GameEngine::globalScene->unpdateRuntimeScene(this->timestep);
        this->render();
        SDL_GL_SwapWindow(this->window);
    }
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}