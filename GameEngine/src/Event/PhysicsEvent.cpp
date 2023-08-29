#include "Event/PhysicsEvent.h"

GameEngine::CollisionEvent::CollisionEvent(ActorData* a, ActorData* b)
    : GameEngine::Event()
    , dataA(a)
    , dataB(b)
{
}

GameEngine::CollisionEvent::~CollisionEvent()
{
    // delete this->dataA;
    // delete this->dataB;
}