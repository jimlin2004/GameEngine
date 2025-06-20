#include "Event/SaveProjectEvent.h"

GameEngineEditor::SaveProjectEvent::SaveProjectEvent()
{
}

GameEngine::EventType GameEngineEditor::SaveProjectEvent::getEventType()
{
    return "SaveProjectEvent";
}