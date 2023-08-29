#include "Script/ScriptInterfaceImplement.h"

#include "Event/Input.h"
#include "Event/Event.h"
#include "Event/EventDispatcher.h"

bool ScriptInterfaceImplement::input_isKeyPressed(GameEngine::KeyCode keyCode)
{
    return GameEngine::Input::isKeyPressed(keyCode);
}

void ScriptInterfaceImplement::addCallback(GameEngine::EventType type, std::function<void(GameEngine::Event& event)> funcPtr)
{
    GameEngine::EventDispatcher::addCallback(type, funcPtr);
}