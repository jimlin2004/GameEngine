#ifndef KEY_UP_EVENT_H
#define KEY_UP_EVENT_H

#include "Event/Event.h"
#include "Event/KeyCode.h"

namespace GameEngine
{
    class KeyUpEvent: public Event
    {
    public:
        explicit KeyUpEvent(KeyCode _key);
        virtual ~KeyUpEvent();
        
        virtual EventType getEventType() override { return EventType::KeyUpEvent; }

        inline KeyCode key() const
        {
            return this->keyCode;
        }
    private:
        KeyCode keyCode;
    };
}

#endif