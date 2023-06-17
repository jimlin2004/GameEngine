#ifndef GE_GAMEENGINEAPI_H
#define GE_GAMEENGINEAPI_H

#include <functional>
#include "GameBaseComponent/GameEventManager/GameEventManager.h"
#include "DataStruct/Vector/Vector.h"
#include "ShaderManager.h"
#include "CameraController.h"
#include "Scene/Scene.h"
#include <functional>

namespace GameEngine
{
    //操作基本底層訪問的api
    class GameEngineAPI
    { 
    private:
        GameEventManager* gameEventManager;
        float _windowWidth, _windowHeight;
        std::function<void()> editorSceneBeginFunc;
    public:
        GameEngineAPI();
        ~GameEngineAPI();
        inline std::function<void()> getEditorSceneFunc() const { return editorSceneBeginFunc; }
        void setEditorSceneFunc(std::function<void()> func);
        void callKeyEvent(int key);
        void addKeyEvent(int key, std::function<void()> func);
        //用來設置全域的window size
        void _setWindowSize(float _w, float _h);
        inline float getWindowWidth() const { return _windowWidth; }
        inline float getWindowHeight() const { return _windowHeight; }
        ShaderManager* shaderManager;
    };

    //整個遊戲引擎的global pointer，勿修改
    //用於訪問基本遊戲操作
    extern GameEngineAPI* GEngine;
    //投影矩陣(將OpenGL正規化的坐標系統轉為視窗座標)
    //由GameBase去bind
    // extern glm::mat4 PROJECTION_MATRIX;
    /*
        全域的Camera
    */
    extern CameraController* cameraController;
}

#endif