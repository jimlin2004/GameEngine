#ifndef IMGUI_PANEL_H
#define IMGUI_PANEL_H

#include "Panel/ImTerminal.h"
#include "Panel/ImSceneHierarchyPanel.h"
#include "Panel/ImPropertiesPanel.h"
#include "Scene/Scene.h"

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
        void renderContentPanel();
        void renderAllPanel(float fps);
    private:
        bool isShowDebug;
        ImTerminal terminal;
        ImSceneHierarchyPanel sceneHierarchyPanel;
        ImPropertiesPanel propertiesPanel;
        GameEngine::Scene* scene;
    };
}

#endif