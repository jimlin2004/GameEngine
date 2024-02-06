#include "Script/Event/KeyDownEvent.h"

GameEngine::Script::KeyDownEvent::KeyDownEvent(GameEngine::KeyCode _key)
    : keyCode(_key)
{
}

GameEngine::Script::KeyDownEvent::~KeyDownEvent()
{
}