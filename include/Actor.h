#ifndef GE_ACTOR_H
#define GE_ACTOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Graphics.h"
#include "ActorComponent/inputComponent/InputComponent.h"

namespace GameEngine
{
    //遊戲中的角色基類(不可使用Input event)
    class Actor
    {
    public:
        float x, y;

        Actor();
        Actor(float x, float y);
        Actor(float x, float y, Graphics::Graphics* graphics);
        virtual void HandleEvent();
        //渲染
        virtual void render();
        //設定角色在世界的位置
        void setPosition(float x, float y);
    protected:
        Graphics::Graphics* texture;
    };

    //可操作的角色(支援Input event)
    class Character: public Actor
    {
    public:
        Character();
        Character(float x, float y);
        Character(float x, float y, Graphics::Graphics* graphics);
        virtual void setInputEvent();


    protected:
        //負責註冊InputEvent的Component
        InputComponent* playerInputComponent;
    };
}

#endif