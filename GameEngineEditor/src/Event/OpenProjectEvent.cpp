#include "Event/OpenProjectEvent.h"

GameEngineEditor::OpenProjectEvent::OpenProjectEvent(const std::string& projectPath)
    : projectPath(projectPath)
{
}

GameEngine::EventType GameEngineEditor::OpenProjectEvent::getEventType()
{
    return "OpenProjectEvent";
}
const std::string GameEngineEditor::OpenProjectEvent::getProjectPath()
{
    return this->projectPath;
}
