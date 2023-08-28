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

void GEngineCore::addCallback(GameEngine::EventType type, std::function<void(const GameEngine::Event &event)> funcPtr)
{
    scriptInterface->addCallback(type, funcPtr);
}

bool GEngineCore::Input::isKeyPressed(GameEngine::KeyCode keyCode)
{
    return scriptInterface->input_isKeyPressed(keyCode);
}
