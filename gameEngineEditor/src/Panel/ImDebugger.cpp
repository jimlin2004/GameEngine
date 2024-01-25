#include "Panel/ImDebugger.h"

#include "imgui.h"

void GameEngineEditor::ImDebugger::render(float fps)
{
    ImGui::Begin("Debug");
        ImGui::Text("FPS: %f", fps);
    ImGui::End();
}