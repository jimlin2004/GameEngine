#ifndef SCRIPT_EVENT_DISPATCHER_H
#define SCRIPT_EVENT_DISPATCHER_H

#include "sol/sol.hpp"
#include <unordered_map>
#include <vector>
#include "Script/Event/ScriptEvent.h"

namespace GameEngine
{
    namespace Script
    {
        struct CallbackFunc
        {
            sol::table luaInstance;
            sol::function func;
        };

        class ScriptEventDispatcherCore
        {
            using EventType = std::string;
        public:
            ScriptEventDispatcherCore() = default;
            void subscribe(EventType type, const sol::function& eventCallback, const sol::table& luaInstance);
            
            template<class TriggeredEventType>
            void invokeCallback(TriggeredEventType* event)
            {
                auto it = this->listeners.find(event->getEventType());
                if (it != this->listeners.end())
                {
                    for (auto& callbackFunc: it->second)
                    {
                        //回傳true為攔截事件
                        if(callbackFunc.func(callbackFunc.luaInstance, *(event)))
                            break;
                    }
                }
            }
            std::unordered_map<EventType, std::vector<CallbackFunc>> listeners;
        };

        //ScriptEventDispatcher的本體
        extern ScriptEventDispatcherCore* scriptEventDispatcherCore;
    }
}

namespace GameEngine
{
    namespace Script
    {
        class ScriptEventDispatcher
        {
            using EventType = std::string;
        public:
            explicit ScriptEventDispatcher();

            static void reset();
            static void addCallback(EventType type, const sol::function& eventCallBack, const sol::table& luaInstance);
            
            template<class TriggeredEventType>
            static void trigger(TriggeredEventType* event)
            {
                GameEngine::Script::scriptEventDispatcherCore->invokeCallback<TriggeredEventType>(event);
            }
        };
    }
    
}



#endif