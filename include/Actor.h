#ifndef ACTOR_H
#define ACTOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Graphics.h"

namespace GameEngine
{
    class Actor
    {
    public:
        float x, y;

        Actor();
        Actor(float x, float y);
        Actor(float x, float y, Graphics::Graphics* graphics);
        virtual void HandleEvent();
        virtual void render();
        void setPosition(float x, float y);
    protected:
        Graphics::Graphics* texture;
    };

    class Character: public Actor
    {
    public:
        Character();
        Character(float x, float y);
        Character(float x, float y, Graphics::Graphics* graphics);
    };
}

#endif