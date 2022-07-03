#include "Arkanoid.h"
#include "Graphics.h"
#include <SDL.h>

Bar::Bar(int x, int y, int w, int h, Color* color): Actor(x, y, w, h)
{
    this->rect = new Rect(x, y, w, h);
    this->color = color;
}

void Bar::Set_x(int x)
{
    this->x = x;
    this->rect->Set_x(x);
    return;
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
    this->Set_x(mx - this->w / 2);
    return;
}

Ball::Ball(int x, int y, int w, int h, Color* color): Actor(x, y, w, h)
{
    this->circle = new Circle(x, y, w / 2);
    this->vec = new Vector(1, 1);
    this->color = color;
}

void Ball::Draw(SDL_Renderer* renderer)
{
    this->circle->Draw(renderer, this->color);
    return;
}

void Ball::Set(int x, int y)
{
    this->x = x;
    this->y = y;
    this->circle->Set(x, y);
    return;
}

void Ball::Update()
{
    this->Set(this->x + this->vec->x, this->y + this->vec->y);
    return;
}

Arkanoid::Arkanoid(const char* title, int width, int height): GameBase(title, width, height)
{
    this->bar = new Bar(0, 450, 60, 10, Color::RGBA(128, 128, 0, 255));
    this->ball = new Ball(10, 10, 8, 8, Color::RGBA(255, 255, 255, 255));
    this->boundary = new Boundary(Point::New(0, 0), Point::New(width, 0), Point::New(width, height), Point::New(0, height));
}

void Arkanoid::Reflex(Actor* actor)
{
    if ((actor->x - actor->w) <= this->boundary->LT->x)
        actor->SetVector(-(actor->vec->x), actor->vec->y);
    else if ((actor->x + actor->w) >= this->boundary->RT->x)
        actor->SetVector(-(actor->vec->x), actor->vec->y);
    else if ((actor->y - actor->h) <= this->boundary->LT->y)
        actor->SetVector(actor->vec->x, -(actor->vec->y));
    else if ((actor->y + actor->h) >= this->boundary->RB->y)
        actor->SetVector(actor->vec->x, -(actor->vec->y));
    return;
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
    this->Clamp(this->bar);
    this->bar->Draw(this->renderer);
    this->ball->Update();
    this->Reflex(this->ball);
    this->ball->Draw(this->renderer);
    SDL_RenderPresent(this->renderer);
}