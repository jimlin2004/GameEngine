#ifndef GAME_ENGINE_PHYSICS_EVENT_H
#define GAME_ENGINE_PHYSICS_EVENT_H

#include "Event/Event.h"
#include "Physics/ActorData.h"

namespace GameEngine
{
    class CollisionEvent: public Event
    {
    public:
        explicit CollisionEvent(ActorData* a, ActorData* b);
        virtual ~CollisionEvent();

        virtual EventType getEventType() override { return "CollisionEvent"; }

        ActorData *dataA, *dataB;
    };
}

#endif