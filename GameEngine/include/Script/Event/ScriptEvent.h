#ifndef SCRIPT_EVENT_H
#define SCRIPT_EVENT_H

#include <string>

namespace GameEngine
{
    namespace Script
    {
        using EventType = std::string;
        class ScriptEvent
        {
        public:
            virtual EventType getEventType() = 0;
        };
    }
}

#endif