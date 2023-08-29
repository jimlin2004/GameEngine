#ifndef SCRIPT_INTERFACE_H
#define SCRIPT_INTERFACE_H

#include <functional>

#include "Event/KeyCode.h"
#include "Event/Event.h"

// pure virtual script interface
// GameEngine 將有一個繼承的子類改變ScriptCore中的scriptInterface
// 如此作為dll與exe的中間溝通層
class ScriptInterface
{
public:
    virtual bool input_isKeyPressed(GameEngine::KeyCode keyCode) = 0;
    virtual void addCallback(GameEngine::EventType type, std::function<void(GameEngine::Event& event)> funcPtr) = 0;
};

#endif