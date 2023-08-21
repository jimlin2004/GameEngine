#include "Script/ScriptEngine.h"

#include "GameEngineAPI/ConsoleApi.h"
#include "Actor/Actor.h"
#include "Core/Platform.h"
#include <unordered_map>
#include "Script/ClassMap.h"
#if USE_WINDOWS
    #include <windows.h>
#endif

#if USE_WINDOWS

struct ScriptEngineData
{
    HMODULE dllModule = NULL;

    GameEngine::ClassMapType* classMapPtr = nullptr;
};

static ScriptEngineData scriptEngineData;

typedef GameEngine::ClassMapType* (WINAPI* getClassMapFuncPtr)();

void GameEngine::ScriptEngine::init(const std::string &dllPath)
{
    scriptEngineData.dllModule = LoadLibrary(dllPath.c_str());
    if (scriptEngineData.dllModule == NULL)
    {
        GameEngine::ConsoleApi::log("[Error] load %s fail\n.", dllPath.c_str());
        return;
    }


}

GameEngine::Actor* GameEngine::ScriptEngine::createActor(const std::string &actorType)
{
    return nullptr;
}

#endif