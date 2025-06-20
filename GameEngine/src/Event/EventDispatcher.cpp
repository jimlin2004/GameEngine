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

void GameEngine::EventDispatcher::subscribe(EventType type, GameEngine::EventDispatcher::EventCallBack eventCallBack)
{
    this->listeners[type].push_back(eventCallBack);
}

void GameEngine::EventDispatcher::invokeCallback(Event* event)
{
    auto it = this->listeners.find(event->getEventType());
    if (it != this->listeners.end())
    {
        for (auto& func: it->second)
        {
            //回傳true為攔截事件
            if(func(event))
                break;
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

void GameEngine::EventDispatcher::addCallback(EventType type, EventCallBack eventCallBack) 
{
    eventDispatcher.subscribe(type, eventCallBack);
}

void GameEngine::EventDispatcher::trigger(Event *event)
{
    eventDispatcher.invokeCallback(event);
}