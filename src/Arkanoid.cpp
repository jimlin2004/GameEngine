#include "Arkanoid.h"
#include "Graphics.h"
#include <SDL.h>

Bar::Bar(int x, int y, int w, int h, Color* color): Actor(x, y, w, h)
{
    this->rect = new Rect(x, y, w, h);
    this->color = color;
}

void Bar::Draw(SDL_Renderer* renderer)
{
    this->rect->Draw(renderer, this->color, true);
    return;
}

void Bar::SetColor(int r, int g, int b, int a)
{
    this->color = Color::RGBA(r, g, b, a);
    return;
}

void Bar::Update()
{
    int mx, my;
    Uint32 button = SDL_GetMouseState(&mx, &my);
    this->rect->Set_x(mx);
    return;
}

Arkanoid::Arkanoid(const char* title, int width, int height): GameBase(title, width, height)
{
    this->bar = new Bar(0, 450, 60, 10, Color::RGBA(255, 255, 255, 255));
}

void Arkanoid::GameContext()
{
    while (SDL_PollEvent(&this->event))
    {
        if (this->event.type == SDL_QUIT)
            this->run = false;
    }
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    this->bar->Update();
    this->bar->Draw(this->renderer);
    SDL_RenderPresent(this->renderer);
}