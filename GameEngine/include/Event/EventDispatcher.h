#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include <unordered_map>
#include <vector>
#include <functional>

#include "Event/Event.h"

namespace GameEngine
{
    //引擎內部使用的Event system
    class EventDispatcher
    {
        using EventType = std::string;
        using EventCallBack = std::function<bool(GameEngine::Event* event)>;
    public:
        explicit EventDispatcher();
        void subscribe(EventType type, EventCallBack eventCallBack);
        void callback(Event* event);

        static void reset();
        static void addCallback(EventType type, EventCallBack eventCallBack);
        static void trigger(Event* event);
    private:
        std::unordered_map<EventType, std::vector<EventCallBack>> listeners;
    };
}

#endif