#ifndef IMGUI_PANEL_H
#define IMGUI_PANEL_H

#include "Panel/ImTerminal.h"
#include "Panel/ImSceneHierarchy.h"
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
        void setSelectedEntity(uint32_t entityID);
        void renderDockspace();
        void renderObjectInformation();
        void renderContentPanel();
        void renderAllPanel(float fps);
    private:
        bool isShowDebug;
        ImTerminal terminal;
        ImSceneHierarchy sceneHierarchyPanel;
        GameEngine::Scene* scene;
    };
}

#endif