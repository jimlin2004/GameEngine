#ifndef ARKANOID_H
#define ARKANOID_H

#include "GameBase.h"
#include "Graphics.h"

class Bar: public Actor
{
public:
    Bar(int x, int y, int w, int h, Color* color);
    virtual void Update() override;
    virtual void Set_x(int x) override;
    virtual void Draw(SDL_Renderer* renderer) override;
    void SetColor(int r, int g, int b, int a);
private:
    Rect* rect;
    Color* color;
};

class Ball: public Actor
{
public:
    Ball(int x, int y, int w, int h, Color* color);
    virtual void Update() override;
    virtual void Draw(SDL_Renderer* renderer) override;
    virtual void Set(int x, int y) override;
private:
    Circle* circle;
    Color* color;
};

class Arkanoid: public GameBase 
{
public:
    Arkanoid(const char* title, int width, int height);
    virtual void GameContext() override;
    void Reflex(Actor* actor);
private:
    Bar* bar;
    Ball* ball;
};

#endif