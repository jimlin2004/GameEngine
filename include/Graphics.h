#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

class Color
{
public:
    Uint8 r, g, b, a;
    Color(short r, short g, short b, short a);
    static Color* RGBA(short r, short g, short b, short a);
};

class Position
{
public:
    int x, y;
    Position();
};

class Graphics
{
public:
    int x, y;
    Graphics();
    Graphics(int x, int y);
};

class Point: public Graphics
{
public:
    Point();
    Point(int x, int y);
    static Point* New(int x, int y);
};

class Rect: public Graphics
{
public:
    SDL_Rect* rect;
    Rect();
    Rect(int x, int y, int w, int h);
    void set_x(int x);
    void set_y(int y);
    void set(int x, int y);
    void draw(SDL_Renderer* renderer, Color* color, bool is_fill);
};

class Circle: public Graphics
{
public:
    int radius;
    Circle();
    Circle(int x, int y, int r);
    void set_x(int x);
    void set_y(int y);
    void set(int x, int y);
    void draw(SDL_Renderer* renderer, Color* color);
};

#endif