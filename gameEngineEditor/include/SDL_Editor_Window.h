#ifndef SDL_EDITOR_WINDOW_H
#define SDL_EDITOR_WINDOW_H

#include "Core/GameBase.h"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

class SDL_Editor_Window: public GameEngine::GameBase
{
public:
    SDL_Editor_Window(const char* title, int width, int height);
    virtual ~SDL_Editor_Window();
    virtual void init() override;
    virtual bool initSDL() override;
    bool initImGui();
    virtual void startGame() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void gameEventHandle() override;

    void bindisFocusOnSDL(bool* ptr);
private:
    bool* isFocusOnSDLPtr;
    bool isCompleteFocusChange;
};

#endif