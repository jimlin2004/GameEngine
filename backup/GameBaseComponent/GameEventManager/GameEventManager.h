#ifndef GE_GAMEEVENTMANAGER_H
#define GE_GAMEEVENTMANAGER_H

#include <list>
#include <unordered_map>
#include <string>
#include <functional>

namespace GameEngine
{
    enum EventType
    {
        KeyEvent = 0
    };

    class GameEventManager
    {
    public:
        GameEventManager();
        void bindKeyEvent(int key, std::function<void()> func);
        void callKeyEvent(int key);
    private:
        //管理Event的Database
        std::unordered_map<int, std::list<std::function<void(void)>>> eventDatabase[1];

        bool checkIsKeyExists(int key);
    };
}

#endif