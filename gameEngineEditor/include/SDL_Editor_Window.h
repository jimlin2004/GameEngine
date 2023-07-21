#ifndef SDL_EDITOR_WINDOW_H
#define SDL_EDITOR_WINDOW_H

#include "Core/Platform.h"

#include "Core/GameBase.h"
#include "Render/Renderer.h"
#include "EditorCamera.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "ImGuizmo/ImGuizmo.h"
#include "MainWindowExportData.h"

class SDL_Editor_Window: public GameEngine::GameBase
{
public:
    SDL_Editor_Window(const char* title, int width, int height);
    virtual ~SDL_Editor_Window();
    virtual void init() override;
    virtual bool initSDL() override;
    bool initImGui();
    virtual void startGame() override;
    virtual void begin() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void gameEventHandle() override;

    void bindIsFocusOnSDL(bool* ptr);
    void bindExportData(GameEngineEditor::ExportData* ptr);
private:
    bool* isFocusOnSDLPtr;
    //imguizmo 的isOver會用到緩存數據(當hoverActor的id不是entt::null才會更新)
    //為了修復此問題所以增加此變數防止點物件再點空的空間再點原物件會點不到的問題
    bool imguizmoVisible;
    ImVec2 viewportSize;
    
    ImGuizmo::OPERATION gizmoOperation;
    GameEngine::FrameBuffer* frameBuffer;
    GameEngine::Actor hoveredActor;
    GameEngineEditor::EditorCamera editorCamera;
    glm::mat4 transform;

    GameEngineEditor::ExportData* mainWindowExportDataPtr;

    void updateEditorCamera(float deltaTime);
};

#endif