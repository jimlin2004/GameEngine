#ifndef CLASS_MAP_H
#define CLASS_MAP_H

#include <string>
#include <unordered_map>
#include <functional>
#include "Script/ScriptEngineMacro.h"
#include "Script/ScriptCore.h"
#include "Script/ScriptInterface.h"
#include "Core/TypeName.hpp"
#include "entt.hpp"

namespace GameEngine
{
    class Character;
    class Scene;

    using ClassMapType = std::unordered_map<std::string, std::function<Character*(entt::entity, Scene*)>>;
    
    // 用於Script engine儲存使用者自訂義scriptable actor的constructor
    // 並做到連接dll及exe作用域的功能
    // [網路資料] windows 中 dll的全域作用域與exe互相獨立
    // 所以需要用dll中的接口函數獲得dll中的ClassMap pointer
    inline ClassMapType* classMap = new ClassMapType(); 

    // 獲得ClassMapType的接口函式
    extern "C" __declspec(dllexport) inline ClassMapType* getClassMap()
    {
        return classMap;
    }

    // 為dll中的scriptInterface bind 為 exe GameEngine中的
    extern "C" __declspec(dllexport) void initDllScriptCore(ScriptInterface* newScriptInterface)
    {
        GEngineCore::initScriptCore(newScriptInterface);
    }

    template<typename T>
    // 此為使用者自訂義的scriptable actor註冊功能
    class ClassFactoryInitializer
    {
    public:
        ClassFactoryInitializer()
        {
            std::string_view strView = TYPE_NAME_BY_TYPE(T);
            std::string typeName = {strView.begin(), strView.end()};
            auto classFactoryFunc = [](entt::entity entityID, Scene* scenePtr){
                T* character = new T();
                character->createActor(entityID, scenePtr);
                return (GameEngine::Character*)character;
            };
            GameEngine::classMap->insert({typeName, classFactoryFunc});
        }
    };

    
    #define REGISTER_CLASS(classTypeName)\
        GameEngine::ClassFactoryInitializer<classTypeName> initializer;
}

#endif