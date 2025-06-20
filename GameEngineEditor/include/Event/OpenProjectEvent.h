#ifndef OPEN_PROJECT_EVENT_H
#define OPEN_PROJECT_EVENT_H

#include "Event/Event.h"
#include <string>

namespace GameEngineEditor
{
    class OpenProjectEvent: public GameEngine::Event
    {
    public:
        OpenProjectEvent(const std::string& projectPath);
        virtual GameEngine::EventType getEventType() override;
        const std::string getProjectPath();
    private:
        std::string projectPath;
    };
}

#endif