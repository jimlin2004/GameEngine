#ifndef GE_COMPONENT_H
#define GE_COMPONENT_H

#include "GameObject.h"

namespace GameEngine
{
    //ActorComponent 基類 (abstract)
    class Component: public GameObject
    {
    public:
        Component();
    };
}


#endif