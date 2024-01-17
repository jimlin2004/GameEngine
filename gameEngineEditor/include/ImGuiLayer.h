#ifndef IMGUI_PANEL_H
#define IMGUI_PANEL_H

namespace GameEngineEditor
{
    class ImGuiLayer
    {
    public:
        static void setup();
        static void renderDockspace();
        static void renderObjectInformation();
        static void renderCollection();
        static void renderContentPanel();
        static void renderAllPanel();
    };
}

#endif