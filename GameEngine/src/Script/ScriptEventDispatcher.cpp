#include "Script/Event/ScriptEventDispatcher.h"

namespace GameEngine
{
    namespace Script
    {
        // event 中樞
        static ScriptEventDispatcher eventDispatcher;
    }
}

GameEngine::Script::ScriptEventDispatcher::ScriptEventDispatcher()
{
}

void GameEngine::Script::ScriptEventDispatcher::subscribe(EventType type, EventCallBack eventCallBack)
{
}

void GameEngine::Script::ScriptEventDispatcher::callback(GameEngine::Script::ScriptEvent *event)
{
}

void GameEngine::Script::ScriptEventDispatcher::reset()
{
}

void GameEngine::Script::ScriptEventDispatcher::addCallback(EventType type, EventCallBack eventCallBack)
{
}

void GameEngine::Script::ScriptEventDispatcher::trigger(GameEngine::Script::ScriptEvent *event)
{
}
