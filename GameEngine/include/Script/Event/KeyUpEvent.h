#ifndef SCRIPT_KEY_UP_EVENT_H
#define SCRIPT_KEY_UP_EVENT_H

#include <cstdint>
#include "Script/Event/ScriptEvent.h"
#include "Event/KeyCode.h"

namespace GameEngine
{
    namespace Script
    {
        class KeyUpEvent: public Script::ScriptEvent
        {
            public:
            explicit KeyUpEvent(KeyCode _key);
            virtual ~KeyUpEvent();
            
            virtual EventType getEventType() override { return "KeyUpEvent"; }

            inline uint32_t key() const
            {
                return (uint32_t)this->keyCode;
            }
        private:
            KeyCode keyCode;
        };
    }
}

#endif