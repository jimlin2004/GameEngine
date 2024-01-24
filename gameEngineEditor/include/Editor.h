#ifndef EDITOR_H
#define EDITOR_H

#include "GL/glew.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_syswm.h"

#include "GameEngineAPI/ConsoleApi.h"
#include "GameEngineAPI/GameEngineAPI.h"
#include "Core/Timestep.h"
#include "Render/Renderer.h"
#include "Opengl/FrameBuffer.h"
#include "Scene/Scene.h"
#include "Actor/Actor.h"
#include "EditorCamera.h"
#include "ProjectParser.h"

#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui.h"
#include "ImGuizmo/ImGuizmo.h"

#include "ImGuiLayer.h"

namespace GameEngineEditor
{
    enum SceneState
    {
        Edit = 0,
        Play
    };

    class Editor
    {
    public:
        Editor(const char* title, int width, int height);
        ~Editor();
        
        bool initAll();
        void start();
    private:
        bool running;
        bool isFocusOnViewport;
        int screenWidth;
        int screenHeight;
        const char* title;
        float fps;
        //imguizmo 的isOver會用到緩存數據(當hoverActor的id不是entt::null才會更新)
        //為了修復此問題所以增加此變數防止點物件再點空的空間再點原物件會點不到的問題
        bool imguizmoVisible;
        ImGuizmo::OPERATION gizmoOperation;
        SDL_Window* window;
        SDL_GLContext GLContext;
        SDL_Event event;
        GameEngine::Timestep timestep;
        uint64_t lastFrameTime;
        GameEngine::FrameBuffer* viewportFrameBuffer;
        GameEngine::FrameBuffer* cameraViewFrameBuffer;
        ImVec2 cameraPreviewSize;
        ImVec2 viewportSize;
        //viewport在screen中的座標
        ImVec2 viewportBound[2];
        GameEngineEditor::EditorCamera editorCamera;
        glm::mat4 transform;
        SceneState sceneState;
        GameEngine::Scene* editorScene;
        GameEngine::Scene* activeScene;
        GameEngine::Actor selectedActor;
        ImGuiLayer imguiLayer;
        GameEngineEditor::ProjectParser projectParser;

        bool initSDL();
        bool initGL();
        bool initImGui();
        
        void initNative();
        void init();
        void begin();
        void update(float deltaTime);
        void render();
        void gameEventHandle();
        
        void logBuildInfo();
        void updateEditorCamera(float deltaTime);

        void openProject(const std::string& projectPath);
    };
}
#endif