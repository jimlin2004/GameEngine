#include "Arkanoid.h"
#include "Graphics.h"
#include <SDL.h>

Bar::Bar(int x, int y, int w, int h, Color* color): Actor(x, y, w, h)
{
    this->rect = new Rect(x, y, w, h);
    this->color = color;
}

void Bar::set_x(int x)
{
    this->x = x;
    this->rect->set_x(x);
    return;
}

void Bar::draw(SDL_Renderer* renderer)
{
    this->rect->draw(renderer, this->color, true);
    return;
}

void Bar::setColor(int r, int g, int b, int a)
{
    this->color = Color::RGBA(r, g, b, a);
    return;
}

void Bar::update()
{
    int mx, my;
    Uint32 button = SDL_GetMouseState(&mx, &my);
    this->set_x(mx - this->w / 2);
    return;
}

Ball::Ball(int x, int y, int w, int h, Color* color): Actor(x, y, w, h)
{
    this->circle = new Circle(x, y, w / 2);
    this->vec = new Vector(1, 1);
    this->color = color;
}

void Ball::draw(SDL_Renderer* renderer)
{
    this->circle->draw(renderer, this->color);
    return;
}

void Ball::set(int x, int y)
{
    this->x = x;
    this->y = y;
    this->circle->set(x, y);
    return;
}

void Ball::update()
{
    this->set(this->x + this->vec->x, this->y + this->vec->y);
    return;
}

Arkanoid::Arkanoid(const char* title, int width, int height): GameBase(title, width, height)
{
    this->bar = new Bar(0, 450, 60, 10, Color::RGBA(128, 128, 0, 255));
    this->registerActor("movable", this->bar);
    this->ball = new Ball(10, 10, 8, 8, Color::RGBA(255, 255, 255, 255));
    this->registerActor("movable", this->ball);
    this->boundary = new Boundary(Point::New(0, 0), Point::New(width, 0), Point::New(width, height), Point::New(0, height));
}

void Arkanoid::reflex(Actor* actor)
{
    if ((actor->x - actor->w) <= this->boundary->LT->x)
        actor->setVector(-(actor->vec->x), actor->vec->y);
    else if ((actor->x + actor->w) >= this->boundary->RT->x)
        actor->setVector(-(actor->vec->x), actor->vec->y);
    else if ((actor->y - actor->h) <= this->boundary->LT->y)
        actor->setVector(actor->vec->x, -(actor->vec->y));
    else if ((actor->y + actor->h) >= this->boundary->RB->y)
        actor->setVector(actor->vec->x, -(actor->vec->y));
    return;
}

void Arkanoid::gameContext()
{
    while (SDL_PollEvent(&this->event))
    {
        if (this->event.type == SDL_QUIT)
            this->run = false;
    }
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    this->bar->update();
    this->clamp(this->bar);
    this->bar->draw(this->renderer);
    this->ball->update();
    this->reflex(this->ball);
    this->ball->draw(this->renderer);
    SDL_RenderPresent(this->renderer);
}