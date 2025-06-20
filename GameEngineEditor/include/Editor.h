#ifndef EDITOR_H
#define EDITOR_H

#include "GL/glew.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_syswm.h"

#include "Core/Timestep.h"
#include "Opengl/FrameBuffer.h"
#include "Scene/Scene.h"
#include "Opengl/Texture.h"
#include "Actor/Actor.h"
#include "EditorCamera.h"
#include "ProjectParser.h"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"
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
        SceneState sceneState;
        bool needToStopScene;
        bool needToStartScene;
        GameEngine::Scene* editorScene;
        GameEngine::Scene* activeScene;
        GameEngine::Actor selectedActor;
        ImGuiLayer imguiLayer;
        GameEngineEditor::ProjectParser projectParser;
        GameEngine::Texture* playBtnIconTexture;
        GameEngine::Texture* stopBtnIconTexture;
        //真正的play button icon，有playBtnIconTexture、stopBtnIconTexture
        GameEngine::Texture* playBtnIcon;

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
        void saveProject();

        void onSceneRuntimeStart();
        void onSceneRuntimeStop();

        float getWindowDpiScale(SDL_Window* window);
    };
}
#endif