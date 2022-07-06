#include "GameBase.h"
#include <SDL.h>
#include <stdio.h>

GameBase::GameBase(const char* title, int width, int height)
{
    this->window = nullptr;
    this->renderer = nullptr;
    this->title = title;
    this->screen_width = width;
    this->screen_height = height;
    this->run = false;
}

bool GameBase::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL Init Error: %s\n", SDL_GetError());
        return false;
    }
    this->window = SDL_CreateWindow(this->title,
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        this->screen_width, 
        this->screen_height,
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

void GameBase::clamp(Actor* actor)
{
    if (actor->x < this->boundary->LT->x)
        actor->set_x(this->boundary->LT->x);
    if (actor->x > (this->boundary->RT->x - actor->w))
        actor->set_x(this->boundary->RT->x - actor->w);
    return;
}

void GameBase::gameContext()
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

void GameBase::startGame()
{
    this->run = true;
    while (run)
    {
        this->gameContext();
    }
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

Boundary::Boundary(): LT(nullptr), RT(nullptr), RB(nullptr), LB(nullptr) {}

Boundary::Boundary(Point* p1, Point* p2, Point* p3, Point* p4)
{
    this->LT = p1;
    this->RT = p2;
    this->RB = p3;
    this->LB = p4;
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

void Actor::setVector(int x, int y)
{
    this->vec = new Vector(x, y);
    return;
}

void Actor::set_x(int x)
{
    this->x = x;
    return;
}

void Actor::set_y(int y)
{
    this->y = y;
    return;
}

void Actor::set(int x, int y)
{
    this->x = x;
    this->y = y;
    return;
}

void Actor::draw(SDL_Renderer* renderer)
{
    return;
}

void Actor::update()
{
    return;
}

void clamp(int &val, int lower_bound, int upper_bound)
{
    if (val > upper_bound)
        val = upper_bound;
    else if (val < lower_bound)
        val = lower_bound;
    return;
}