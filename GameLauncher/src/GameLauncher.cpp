#include "GameLauncher.h"

#include "GameEngineAPI/ConsoleApi.h"
#include "GameEngineAPI/GameEngineAPI.h"
#include "Render/Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Math/Math.h"
#include "Core/CameraController.h"
#include "Opengl/TextureManager.h"
#include "Event/Input.h"
#include "Scene/SceneSerializer.h"

#include <filesystem>

//Script
#include "Script/Event/ScriptEventDispatcher.h"
#include "Script/Event/KeyDownEvent.h"
#include "Script/Event/KeyUpEvent.h"


GameLauncher::GameLauncher(const char * title, int width, int height, const std::string& currPath)
    : GameEngine::GameBase(title, width, height)
    , currPath(currPath)
    , scene(new GameEngine::Scene())
{
}


bool GameLauncher::initAll()
{
    bool result = this->initSDL() && this->initGL();
    if (!result)
        return false;
    this->init();
    return true;
}


void GameLauncher::gameEventHandle()
{
    while (SDL_PollEvent(&this->event))
    {
        switch (this->event.type)
        {
            case SDL_QUIT:
                this->running = false;
                break;
            case SDL_KEYDOWN:
            {
                if (this->event.key.repeat == 0)
                {
                    GameEngine::Script::KeyDownEvent keyDownEvent((GameEngine::KeyCode)(this->event.key.keysym.scancode));
                    GameEngine::Script::ScriptEventDispatcher::trigger<GameEngine::Script::KeyDownEvent>(&keyDownEvent);
                }
                break;
            }
            case SDL_KEYUP:
            {
                if (this->event.key.repeat == 0)
                {
                    GameEngine::Script::KeyUpEvent keyUpEvent((GameEngine::KeyCode)(this->event.key.keysym.scancode));
                    GameEngine::Script::ScriptEventDispatcher::trigger<GameEngine::Script::KeyUpEvent>(&keyUpEvent);
                }
                break;
            }
            default:
                break;
        }
    }
}


void GameLauncher::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GameEngine::GEngine->textureManager->processCreateTextureTasks();

    GameEngine::Renderer::begin((*GameEngine::cameraController->getCamera()), GameEngine::cameraController->getTransform());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->scene->render();
    GameEngine::Renderer::close();

}


void GameLauncher::update(float deltaTime)
{
    this->scene->updateRuntimeScene(deltaTime);
}


void GameLauncher::parseProject(const std::string& projectName)
{
    std::filesystem::path mapPath(this->currPath);
    mapPath /= "assets/scene/" + projectName + ".map";
    if (std::filesystem::exists(mapPath))
    {
        GameEngine::SceneSerializer sceneSerializer(&this->scene);
        if (sceneSerializer.deserialize(mapPath.string()))
        {
            GameEngine::ConsoleApi::log("Load scene success.\n");
        }
        else
        {
            GameEngine::ConsoleApi::log("Fail to load scene.\n");
        }
    }
}

void GameLauncher::startGame()
{
    this->begin();
    this->running = true;
    uint64_t time = SDL_GetPerformanceCounter();

    this->scene->onRuntimeStart(this->currPath);

    while (this->running)
    {
        this->lastFrameTime = time;
        time = SDL_GetPerformanceCounter();
        this->timestep = ((time - this->lastFrameTime) * 1000.0f / SDL_GetPerformanceFrequency()) * 0.001f;
        // this->fps = 1.0 / ((time - this->lastFrameTime) / (float)SDL_GetPerformanceFrequency());
        this->gameEventHandle();

        this->update(this->timestep);
        this->render();
        SDL_GL_SwapWindow(this->window);
    }
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}