#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "../Component/Component.h"
#include <functional>

namespace GameEngine
{
    class InputComponent: public Component
    {
    public:
        InputComponent();
        void bindKeyEvent(int key, std::function<void()> func);
    };
}

#endif