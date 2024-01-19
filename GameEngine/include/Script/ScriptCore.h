#ifndef SCRIPT_COER_H
#define SCRIPT_COER_H

#include "Script/ScriptEngineMacro.h"
#include "Event/KeyCode.h"
#include "Event/Event.h"
#include <functional>

class ScriptInterface;

namespace GEngineCore
{
    //初始化ScriptCore.cpp中的scriptInterface
    void initScriptCore(ScriptInterface* newScriptInterface);
    ScriptInterface* getScriptInterface();

    class Input
    {
    public:
        static bool isKeyPressed(GameEngine::KeyCode keyCode);
    };

    void addCallback(GameEngine::EventType type, std::function<bool(GameEngine::Event* event)> funcPtr);
}

#endif