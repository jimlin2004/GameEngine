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
        class ScriptEventDispatcher
        {
            using EventType = std::string;
            using EventCallBack = sol::function;
        public:
            explicit ScriptEventDispatcher();
            void subscribe(EventType type, EventCallBack eventCallBack);
            void callback(ScriptEvent* event);

            static void reset();
            static void addCallback(EventType type, EventCallBack eventCallBack);
            static void trigger(ScriptEvent* event);
        private:
            std::unordered_map<EventType, std::vector<EventCallBack>> listeners;
        };
    }
    
}

#endif