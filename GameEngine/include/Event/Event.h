#ifndef GAME_ENGINE_EVENT_H
#define GAME_ENGINE_EVENT_H

#include <string>

namespace GameEngine
{
    using EventType = std::string;
    class Event
    {
    public:
        virtual EventType getEventType() = 0;
    };
}

#endif