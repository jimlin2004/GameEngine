#ifndef MOUSE_CODE_H
#define MOUSE_CODE_H

#include "SDL2/SDL_mouse.h"

namespace GameEngine
{
    enum MouseCode
    {
        Mouse_BUTTON_LEFT = SDL_BUTTON_LEFT,
        Mouse_BUTTON_MIDDLE = SDL_BUTTON_MIDDLE,
        Mouse_BUTTON_RIGHT = SDL_BUTTON_RIGHT,
        Mouse_BUTTON_X1 = SDL_BUTTON_X1,
        Mouse_BUTTON_X2 = SDL_BUTTON_X2
    };
}

#endif