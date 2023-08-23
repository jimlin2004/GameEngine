#include "Script/ScriptCore.h"

#include "Script/ScriptInterface.h"

static ScriptInterface* scriptInterface = nullptr;

void GEngineCore::initScriptCore(ScriptInterface* newScriptInterface)
{
    scriptInterface = newScriptInterface;
}

ScriptInterface *GEngineCore::getScriptInterface()
{
    return scriptInterface;
}

bool GEngineCore::Input::isKeyPressed(GameEngine::KeyCode keyCode)
{
    return scriptInterface->input_isKeyPressed(keyCode);
}
