#include "GameBase.h"
#include <SDL.h>
#include <stdio.h>

GameBase::GameBase(const char* title, int width, int height)
{
    this->window = nullptr;
    this->renderer = nullptr;
    this->title = title;
    this->SCREEN_HEIGHT = height;
    this->SCREEN_WIDTH = width;
    this->run = false;
}

bool GameBase::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL Init Error: %s\n", SDL_GetError());
        return false;
    }
    this->window = SDL_CreateWindow(this->title,
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        this->SCREEN_WIDTH, 
        this->SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!this->window)
    {
        printf("Create Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    this->renderer = SDL_CreateRenderer(this->window, 
        -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->renderer)
    {
        SDL_DestroyWindow(this->window);
        printf("SDL CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    return true;
}

void GameBase::GameContext()
{
    while (SDL_PollEvent(&this->event))
    {
        if (this->event.type == SDL_QUIT)
            this->run = false;
    }
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);
}

void GameBase::StartGame()
{
    this->run = true;
    while (run)
    {
        this->GameContext();
    }
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

Actor::Actor() 
{
    this->x = this->y = this->w = this->h = 0;
    this->vec = nullptr;
}

Actor::Actor(int x, int y)
{
    this->x = x;
    this->y = y;
    this->w = this->h = 0;
    this->vec = nullptr;
}

Actor::Actor(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->vec = nullptr;
}

void Actor::SetVector(int x, int y)
{
    this->vec = new Vector(x, y);
    return;
}

void Actor::Draw(SDL_Renderer* renderer)
{
    return;
}

void Actor::Update()
{
    return;
}