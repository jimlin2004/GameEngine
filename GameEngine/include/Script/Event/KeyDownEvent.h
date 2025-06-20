#ifndef SCRIPT_KEY_DOWN_EVENT_H
#define SCRIPT_KEY_DOWN_EVENT_H

#include <cstdint>
#include "Script/Event/ScriptEvent.h"
#include "Event/KeyCode.h"

namespace GameEngine
{
    namespace Script
    {
        class KeyDownEvent: public Script::ScriptEvent
        {
            public:
            explicit KeyDownEvent(KeyCode _key);
            virtual ~KeyDownEvent();
            
            virtual EventType getEventType() override { return "KeyDownEvent"; }

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