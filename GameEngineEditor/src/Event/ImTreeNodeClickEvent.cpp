#include "Event/ImTreeNodeClickEvent.h"

GameEngineEditor::ImTreeNodeClickEvent::ImTreeNodeClickEvent(uint32_t selectedEntityID)
    : selectedEntityID(selectedEntityID)
{
}

GameEngine::EventType GameEngineEditor::ImTreeNodeClickEvent::getEventType()
{
    return "ImTreeNodeClickEvent";
}
uint32_t GameEngineEditor::ImTreeNodeClickEvent::getSelectedEntityID()
{
    return this->selectedEntityID;
}
