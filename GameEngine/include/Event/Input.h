#ifndef INPUT_H
#define INPUT_H

#include "KeyCode.h"
#include "MouseCode.h"
#include "glm/glm.hpp"

namespace GameEngine
{
    struct MousePosition
    {
        float x, y;
        operator glm::vec2 ();
    };
    
    class Input
    {
    public:
        static bool isKeyPressed(KeyCode keyCode);
        static bool isMouseButtonPressed(MouseCode mouseCode);
        static MousePosition getMousePosition();
        static void getMousePosition(int* x, int* y);
        static int getMouseX();
        static void getMouseX(int* x);
        static int getMouseY();
        static void getMouseY(int* y);
    private:
        static const uint8_t* keyboardState;
    };
}


#endif