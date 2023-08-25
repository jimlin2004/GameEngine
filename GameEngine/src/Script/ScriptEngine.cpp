#include "Script/ScriptEngine.h"

#include "GameEngineAPI/ConsoleApi.h"
#include "Script/Character.h"
#include "Core/Platform.h"
#include <unordered_map>
#include "Script/ClassMap.h"
#include "Script/ScriptInterfaceImplement.h"
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

typedef GameEngine::ClassMapType* (WINAPI* GetClassMapFuncPtr)();
typedef void (WINAPI* InitDllScriptCoreFuncPtr)(ScriptInterface*);

void GameEngine::ScriptEngine::init(const std::string &dllPath)
{
    scriptEngineData.dllModule = LoadLibrary(dllPath.c_str());
    if (scriptEngineData.dllModule == NULL)
    {
        GameEngine::ConsoleApi::log("[Error] load %s fail.\n", dllPath.c_str());
        return;
    }

    GetClassMapFuncPtr getClassMapFuncPtr = (GetClassMapFuncPtr)GetProcAddress(scriptEngineData.dllModule, "getClassMap");
    if (getClassMapFuncPtr == nullptr)
    {
        GameEngine::ConsoleApi::log("[Error] load getClassMap function fail.\n");
        return;
    }

    scriptEngineData.classMapPtr = getClassMapFuncPtr();
    
    InitDllScriptCoreFuncPtr initDllScriptCoreFuncPtr = (InitDllScriptCoreFuncPtr)GetProcAddress(scriptEngineData.dllModule, "initDllScriptCore");
    if (initDllScriptCoreFuncPtr == nullptr)
    {
        GameEngine::ConsoleApi::log("[Error] load initDllScriptCore function fail.\n");
        return;
    }
    static ScriptInterfaceImplement* scriptInterfaceImplement = new ScriptInterfaceImplement();
    initDllScriptCoreFuncPtr(scriptInterfaceImplement);
}

void GameEngine::ScriptEngine::stop()
{
    if (scriptEngineData.dllModule != NULL)
    {
        FreeLibrary(scriptEngineData.dllModule);
        scriptEngineData.dllModule = NULL;
    }
}

void GameEngine::ScriptEngine::reload(const std::string &dllPath)
{
    GameEngine::ScriptEngine::stop();
    GameEngine::ScriptEngine::init(dllPath);
}

GameEngine::Character* GameEngine::ScriptEngine::createActor(const std::string &actorType, entt::entity entityID, Scene* scenePtr)
{
    return (*scriptEngineData.classMapPtr)[actorType](entityID, scenePtr);
}

std::vector<std::string> GameEngine::ScriptEngine::getAllClassName()
{
    std::vector<std::string> classVec;
    for (auto& p: *(scriptEngineData.classMapPtr))
    {
        classVec.emplace_back(p.first);
    }
    return classVec;
}

#endif