#ifndef SDL_EDITOR_WINDOW_H
#define SDL_EDITOR_WINDOW_H

#include "Core/Platform.h"

#include "Core/GameBase.h"
#include "Render/Renderer.h"

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
    ImVec2 viewportSize;
    
    ImGuizmo::OPERATION gizmoOperation;
    GameEngine::FrameBuffer* frameBuffer;
    GameEngine::Actor hoveredActor;

    GameEngineEditor::ExportData* mainWindowExportDataPtr;

    void updateEditorCamera(float deltaTime);
};

#endif