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

Graphics::Graphics()
{
    this->x = 0;
    this->y = 0;
}

Graphics::Graphics(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point::Point(): Graphics()
{
    return;
}

Point::Point(int x, int y): Graphics(x, y)
{
    return;
}

Point* Point::New(int x, int y)
{
    return new Point(x, y);
}

Rect::Rect(): Graphics()
{
    this->rect = nullptr;
}

Rect::Rect(int x, int y, int w, int h): Graphics(x, y)
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

Circle::Circle(): Graphics() 
{
    return;
};

Circle::Circle(int x, int y, int r): Graphics(x, y)
{
    this->radius = r;
    return;
}

void Circle::Set_x(int x)
{
    this->x = x;
    return;
}

void Circle::Set_y(int y)
{
    this->y = y;
    return;
}

void Circle::Set(int x, int y)
{
    this->x = x;
    this->y = y;
    return;
}

void Circle::Draw(SDL_Renderer* renderer, Color* color)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    int a_x = 0;
    int a_y = this->radius;
    int m = 5 - 4 * this->radius;
    while (a_x <= a_y)
    {
        SDL_RenderDrawLine(renderer, this->x - a_y, this->y - a_x, this->x + a_y, this->y - a_x);
        SDL_RenderDrawLine(renderer, this->x - a_y, this->y + a_x, this->x + a_y, this->y + a_x);
        if (m > 0)
        {
            SDL_RenderDrawLine(renderer, this->x - a_x, this->y - a_y, this->x + a_x, this->y - a_y);
            SDL_RenderDrawLine(renderer, this->x - a_x, this->y + a_y, this->x + a_x, this->y + a_y);
            a_y--;
            m -= 8 * a_y;
        }
        a_x++;
        m += 8 * a_x + 4;
    }
}