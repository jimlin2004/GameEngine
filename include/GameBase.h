#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "Vector.h"
#include "Graphics.h"
#include <SDL.h>

class GameBase
{
public:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    const char* title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool run;
    SDL_Event event;

    GameBase(const char* title, int width, int height);
    bool Init();
    virtual void GameContext();
    virtual void StartGame();
};

class Actor
{
public:
    int x, y, w, h;
    Vector* vec;

    Actor();
    Actor(int x, int y);
    Actor(int x, int y, int w, int h);
    void SetVector(int x, int y);
    virtual void Update();
    virtual void Draw(SDL_Renderer* renderer);
};

#endif