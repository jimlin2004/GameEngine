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
#include "EditorCamera.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "ImGuizmo/ImGuizmo.h"

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
        SDL_Window* window;
        SDL_GLContext GLContext;
        SDL_Event event;
        GameEngine::Timestep timestep;
        uint64_t lastFrameTime;
        GameEngine::FrameBuffer* frameBuffer;
        ImVec2 viewportSize;
        GameEngineEditor::EditorCamera editorCamera;
        glm::mat4 transform;
        SceneState sceneState;

        bool initSDL();
        bool initGL();
        bool initImGui();
        
        void init();
        void update(float deltaTime);
        void render();
        void gameEventHandle();
        void begin();
        void logBuildInfo();
        void updateEditorCamera(float deltaTime);
    };
}
#endif