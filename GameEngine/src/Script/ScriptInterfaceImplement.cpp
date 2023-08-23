#include "Script/ScriptInterfaceImplement.h"

#include "Event/Input.h"

bool ScriptInterfaceImplement::input_isKeyPressed(GameEngine::KeyCode keyCode)
{
    return GameEngine::Input::isKeyPressed(keyCode);
}