#ifndef KEY_DOWN_EVENT_H
#define KEY_DOWN_EVENT_H

#include "Event/Event.h"
#include "Event/KeyCode.h"

namespace GameEngine
{
    class KeyDownEvent: public Event
    {
    public:
        explicit KeyDownEvent(KeyCode _key);
        virtual ~KeyDownEvent();
        
        virtual EventType getEventType() override { return EventType::KeyDownEvent; }

        inline KeyCode key() const
        {
            return this->keyCode;
        }
    private:
        KeyCode keyCode;
    };
}

#endif