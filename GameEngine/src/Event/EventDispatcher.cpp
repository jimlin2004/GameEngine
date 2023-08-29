#include "Event/EventDispatcher.h"

#include "Event/PhysicsEvent.h"

namespace GameEngine
{
    // event 中樞
    static EventDispatcher eventDispatcher;
}

GameEngine::EventDispatcher::EventDispatcher()
{
}

void GameEngine::EventDispatcher::subscribe(EventType type, GameEngine::EventDispatcher::EventFunc eventFunc)
{
    this->listeners[type].push_back(eventFunc);
}

void GameEngine::EventDispatcher::callback(Event& event)
{
    auto it = this->listeners.find(event.getEventType());
    if (it != this->listeners.end())
    {
        for (auto& func: it->second)
        {
            func(event);
        }
    }
}

void GameEngine::EventDispatcher::reset()
{
    for (auto& p: eventDispatcher.listeners)
    {
        p.second.clear();
    }
}

void GameEngine::EventDispatcher::addCallback(EventType type, EventFunc eventFunc) 
{
    eventDispatcher.subscribe(type, eventFunc);
}

void GameEngine::EventDispatcher::trigger(Event &event)
{
    eventDispatcher.callback(event);
}