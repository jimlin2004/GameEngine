#ifndef ACTOR_DATA_H
#define ACTOR_DATA_H

#include "Actor/Actor.h"

namespace GameEngine
{
    class Scene;
    // 用於box2d contact callback，存於b2Body
    class ActorData
    {
    public:
        explicit ActorData(entt::entity entityID, Scene* scenePtr);
        ~ActorData();
        std::string getTag();
        Actor actor;
    };
}

#endif