#ifndef IMGUI_PANEL_H
#define IMGUI_PANEL_H

#include "Panel/ImTerminal.h"
#include "Panel/ImSceneHierarchyPanel.h"
#include "Panel/ImPropertiesPanel.h"
#include "Panel/ImContentBrowserPanel.h"
#include "Panel/ImCameraPreview.h"
#include "Scene/Scene.h"

#include "Core/Platform.h"
#if USE_WINDOWS
    #include <windows.h>
#endif

namespace GameEngineEditor
{
    class ImGuiLayer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();
        void setup();
        void setScene(GameEngine::Scene* scene);
        void setSelectedEntityID(uint32_t entityID);
        void renderDockspace();
        void renderCameraPreview(void* textureID, float aspectRatio);
        void renderAllPanel(float fps);
        void setProjectRootPath(const std::string& rootPath);

        void eventHandle();

        inline ImVec2 getCameraPreviewSize() { return this->cameraPreview.getViewportSize(); }
    #if USE_WINDOWS
        void setWindowID(HWND windowID);
    #endif
    private:
        bool isShowDebug;
        ImTerminal terminal;
        ImSceneHierarchyPanel sceneHierarchyPanel;
        ImPropertiesPanel propertiesPanel;
        ImContentBrowserPanel contentBrowserPanel;
        ImCameraPreview cameraPreview;
        GameEngine::Scene* scene;
    #if USE_WINDOWS
        HWND windowID;
    #endif
    };
}

#endif