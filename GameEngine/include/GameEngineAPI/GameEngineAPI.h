#ifndef GE_GAMEENGINEAPI_H
#define GE_GAMEENGINEAPI_H

#include <functional>
#include "Opengl/ShaderManager.h"
#include "Opengl/TextureManager.h"
#include "Core/CameraController.h"
#include "Scene/Scene.h"
#include <functional>

namespace GameEngine
{
    //操作基本底層訪問的api
    class GameEngineAPI
    { 
    private:
        float _windowWidth, _windowHeight;
        std::string workingDirname;
        std::function<void()> editorSceneBeginFunc;
    public:
        GameEngineAPI();
        ~GameEngineAPI();
        inline std::function<void()> getEditorSceneFunc() const { return editorSceneBeginFunc; }
        void setEditorSceneFunc(std::function<void()> func);
        //用來設置全域的window size
        void _setWindowSize(float _w, float _h);
        void setWorkingDirname(const std::string& path);
        inline float getWindowWidth() const { return _windowWidth; }
        inline float getWindowHeight() const { return _windowHeight; }
        inline std::string getWorkingDirname() const { return this->workingDirname; }
        ShaderManager* shaderManager;
        TextureManager* textureManager;
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