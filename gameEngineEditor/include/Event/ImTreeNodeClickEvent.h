#ifndef IMTREE_NODE_CLICK_EVENT_H
#define IMTREE_NODE_CLICK_EVENT_H

#include "Event/Event.h"

namespace GameEngineEditor
{
    class ImTreeNodeClickEvent: public GameEngine::Event
    {
    public:
        ImTreeNodeClickEvent(uint32_t selectedEntityID);
        virtual GameEngine::EventType getEventType() override;
        uint32_t getSelectedEntityID();
    private:
        uint32_t selectedEntityID;
    };
}

#endif