#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "Vector.h"
#include "Graphics.h"
#include <SDL.h>

class Boundary
{
public:
    Point *LT, *RT, *RB, *LB;
    Boundary();
    Boundary(Point* p1, Point* p2, Point* p3, Point* p4);
};

class Actor
{
public:
    int x, y, w, h;
    Vector* vec;

    Actor();
    Actor(int x, int y);
    Actor(int x, int y, int w, int h);
    void setVector(int x, int y);
    virtual void set_x(int x);
    virtual void set_y(int y);
    virtual void set(int x, int y);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
};
class GameBase
{
public:
    int screen_width;
    int screen_height;
    const char* title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool run;
    SDL_Event event;
    Boundary* boundary;

    GameBase(const char* title, int width, int height);
    bool init();
    void clamp(Actor* actor);
    virtual void gameContext();
    virtual void startGame();
};
#endif