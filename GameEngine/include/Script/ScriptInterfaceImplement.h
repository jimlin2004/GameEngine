#ifndef SCRIPT_INTERFACE_IMPLEMENT_H
#define SCRIPT_INTERFACE_IMPLEMENT_H

#include "Script/ScriptInterface.h"

class ScriptInterfaceImplement: public ScriptInterface
{
public:
    virtual bool input_isKeyPressed(GameEngine::KeyCode keyCode);
};

#endif