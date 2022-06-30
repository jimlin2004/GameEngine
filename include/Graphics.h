#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

class Color
{
public:
    short r, g, b, a;
    Color(short r, short g, short b, short a);
    static Color* RGBA(short r, short g, short b, short a);
};

class Position
{
public:
    Position();
    int x, y;
};

class Rect
{
public:
    SDL_Rect* rect;
    Rect();
    Rect(int x, int y, int w, int h);
    void Set_x(int x);
    void Set_y(int y);
    void Set(int x, int y);
    void Draw(SDL_Renderer* renderer, Color* color, bool is_fill);
};

#endif