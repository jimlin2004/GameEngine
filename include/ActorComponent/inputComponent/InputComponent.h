#ifndef GE_INPUTCOMPONENT_H
#define GE_INPUTCOMPONENT_H

#include "../Component/Component.h"
#include "GameEngineAPI/GameEngineAPI.h"
#include <functional>

namespace GameEngine
{
    //用於註冊Input event
    class InputComponent: public Component
    {
    public:
        InputComponent();
        //向GEngine註冊Input event
        void bindKeyEvent(int key, std::function<void()> func);
    };
}

#endif