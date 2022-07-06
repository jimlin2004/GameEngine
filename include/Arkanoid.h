#ifndef ARKANOID_H
#define ARKANOID_H

#include "GameBase.h"
#include "Graphics.h"

class Bar: public Actor
{
public:
    Bar(int x, int y, int w, int h, Color* color);
    virtual void update() override;
    virtual void set_x(int x) override;
    virtual void draw(SDL_Renderer* renderer) override;
    void setColor(int r, int g, int b, int a);
private:
    Rect* rect;
    Color* color;
};

class Ball: public Actor
{
public:
    Ball(int x, int y, int w, int h, Color* color);
    virtual void update() override;
    virtual void draw(SDL_Renderer* renderer) override;
    virtual void set(int x, int y) override;
private:
    Circle* circle;
    Color* color;
};

class Arkanoid: public GameBase 
{
public:
    Arkanoid(const char* title, int width, int height);
    virtual void gameContext() override;
    void reflex(Actor* actor);
private:
    Bar* bar;
    Ball* ball;
};

#endif