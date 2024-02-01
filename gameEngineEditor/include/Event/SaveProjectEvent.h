#ifndef SAVE_PROJECT_EVENT_H
#define SAVE_PROJECT_EVENT_H

#include "Event/Event.h"
#include <string>

namespace GameEngineEditor
{
    class SaveProjectEvent: public GameEngine::Event
    {
    public:
        SaveProjectEvent();
        virtual GameEngine::EventType getEventType() override;
    };
}

#endif