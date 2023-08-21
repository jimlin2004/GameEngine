#ifndef CLASS_MAP
#define CLASS_MAP

#include <unordered_map>
#include <functional>
#include <type_traits>
#include "Script/ScriptEngineMacro.h"
#include "Actor/Actor.h"

namespace GameEngine
{
    using ClassMapType = std::unordered_map<std::string, std::function<Actor*()>>;
    
    // 用於Script engine儲存使用者自訂義scriptable actor的constructor
    // 並做到連接dll及exe作用域的功能
    // [網路資料] windows 中 dll的全域作用域與exe互相獨立
    // 所以需要用dll中的接口函數獲得dll中的ClassMap pointer
    inline ClassMapType* classMap = new ClassMapType(); 

    extern "C" GENGINE_API inline ClassMapType* getClassMap()
    {
        return classMap;
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
            auto classFactoryFunc = [](){
                return (Actor*)new T();
            };
            GameEngine::classMap->insert({typeName, classFactoryFunc});
        }
    };

    
    #define REGISTER_CLASS(classTypeName)\
        GameEngine::ClassFactoryInitializer<classTypeName> initializer;
}

#endif