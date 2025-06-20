#include "Script/Event/KeyUpEvent.h"

GameEngine::Script::KeyUpEvent::KeyUpEvent(GameEngine::KeyCode _key)
    : keyCode(_key)
{
}

GameEngine::Script::KeyUpEvent::~KeyUpEvent()
{
}