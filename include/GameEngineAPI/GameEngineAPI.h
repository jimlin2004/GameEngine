#ifndef GE_GAMEENGINEAPI_H
#define GE_GAMEENGINEAPI_H

#include <functional>
#include "../GameBaseComponent/GameEventManager/GameEventManager.h"
#include "../DataStruct/Vector/Vector.h"


namespace GameEngine
{
    //操作基本底層訪問的api
    class GameEngineAPI
    {
    public:
        GameEngineAPI();
        //template 需要實現在template裡，不可分

        template<class TActor, class TGraphics>
        TActor* spawnActor(TGraphics* graphics)
        {
            TActor* obj = new TActor(graphics->getX(), graphics->getY(), graphics);
            return obj;
        }

        template<class TActor>
        TActor* spawnActor(Vector* _vec)
        {
            TActor* obj = new TActor(_vec->x, _vec->y);
            return obj;
        }
        void callKeyEvent(int key);
        void addKeyEvent(int key, std::function<void()> func);
    private:
        GameEventManager* gameEventManager;
    };

    //整個遊戲引擎的global pointer，勿修改
    //用於訪問基本遊戲操作
    extern GameEngineAPI* GEngine;
}

#endif