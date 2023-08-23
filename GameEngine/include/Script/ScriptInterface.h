#ifndef SCRIPT_INTERFACE_H
#define SCRIPT_INTERFACE_H

#include "Event/KeyCode.h"

// pure virtual script interface
// GameEngine 將有一個繼承的子類改變ScriptCore中的scriptInterface
// 如此作為dll與exe的中間溝通層
class ScriptInterface
{
public:
    virtual bool input_isKeyPressed(GameEngine::KeyCode keyCode) = 0;
};

#endif