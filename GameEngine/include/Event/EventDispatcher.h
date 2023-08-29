#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include <unordered_map>
#include <vector>
#include <functional>

#include "Event/Event.h"

namespace GameEngine
{
    class EventDispatcher
    {
        using EventFunc = std::function<void(GameEngine::Event& event)>; 
    public:
        explicit EventDispatcher();
        void subscribe(EventType type, EventFunc eventFunc);
        void callback(Event& event);

        static void reset();
        static void addCallback(EventType type, EventFunc eventFunc);
        static void trigger(Event& event);
    private:
        std::unordered_map<EventType, std::vector<EventFunc>> listeners;
    };
}

#endif