#include "Script/Event/ScriptEventDispatcher.h"

namespace GameEngine
{
    namespace Script
    {
        ScriptEventDispatcherCore* scriptEventDispatcherCore = new ScriptEventDispatcherCore();
    }
}

void GameEngine::Script::ScriptEventDispatcherCore::subscribe(EventType type, const sol::function& eventCallBack, const sol::table& luaInstance)
{
    this->listeners[type].push_back({luaInstance, eventCallBack});
}

GameEngine::Script::ScriptEventDispatcher::ScriptEventDispatcher()
{
}

void GameEngine::Script::ScriptEventDispatcher::reset()
{
    for (auto& p: GameEngine::Script::scriptEventDispatcherCore->listeners)
    {
        p.second.clear();
    }
}

void GameEngine::Script::ScriptEventDispatcher::addCallback(EventType type, const sol::function& eventCallBack, const sol::table& luaInstance)
{
    GameEngine::Script::scriptEventDispatcherCore->subscribe(type, eventCallBack, luaInstance);
}