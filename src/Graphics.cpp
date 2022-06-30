#include "Graphics.h"
#include <SDL.h>

Color::Color(short r, short g, short b, short a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color* Color::RGBA(short r, short g, short b, short a)
{
    return new Color(r, g, b, a);
}

Position::Position()
{
    this->x = 0;
    this->y = 0;
}

Rect::Rect()
{
    this->rect = nullptr;
}

Rect::Rect(int x, int y, int w, int h)
{
    this->rect = new SDL_Rect();
    this->rect->x = x;
    this->rect->y = y;
    this->rect->w = w;
    this->rect->h = h;
}

void Rect::Set_x(int x)
{
    this->rect->x = x;
    return;
}

void Rect::Set_y(int y)
{
    this->rect->y = y;
    return;
}

void Rect::Set(int x, int y)
{
    this->rect->x = x;
    this->rect->y = y;
    return;
}

void Rect::Draw(SDL_Renderer* renderer, Color* color, bool is_fill)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    if (is_fill)
        SDL_RenderFillRect(renderer, this->rect);
    else
        SDL_RenderDrawRect(renderer, this->rect);
    return;
}