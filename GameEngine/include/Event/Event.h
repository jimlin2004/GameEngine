#ifndef GAME_ENGINE_EVENT_H
#define GAME_ENGINE_EVENT_H

namespace GameEngine
{
    enum class EventType
    {
        None = 0,
        KeyDownEvent,
        KeyUpEvent,
        CollisionEvent
    };

    class Event
    {
    public:
        virtual EventType getEventType() = 0;
    };
}

#endif