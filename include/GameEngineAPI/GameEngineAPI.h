#ifndef GE_GAMEENGINEAPI_H
#define GE_GAMEENGINEAPI_H

#include <functional>
#include "../GameBaseComponent/GameEventManager/GameEventManager.h"
#include "../DataStruct/Vector/Vector.h"
#include "../ShaderManager.h"
#include "../../third_party/glm/glm.hpp"
#include "../../third_party/glm/gtc/matrix_transform.hpp"

namespace GameEngine
{
    //操作基本底層訪問的api
    class GameEngineAPI
    { 
    private:
        GameEventManager* gameEventManager;
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
        ShaderManager* shaderManager;
    };

    //整個遊戲引擎的global pointer，勿修改
    //用於訪問基本遊戲操作
    extern GameEngineAPI* GEngine;
    //投影矩陣(將OpenGL正規化的坐標系統轉為視窗座標)
    //由GameBase去bind
    extern glm::mat4 PROJECTION_MATRIX;
}

#endif