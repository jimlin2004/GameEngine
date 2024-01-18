#ifndef IMGUI_PANEL_H
#define IMGUI_PANEL_H

#include "ImTerminal.h"

namespace GameEngineEditor
{
    class ImGuiLayer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();
        void setup();
        void renderDockspace();
        void renderObjectInformation();
        void renderCollection();
        void renderContentPanel();
        void renderAllPanel();
    private:
        bool isShowDebug;
        ImTerminal terminal;
    };
}

#endif