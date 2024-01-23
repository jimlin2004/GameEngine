#include "Panel/ImCameraPreview.h"

GameEngineEditor::ImCameraPreview::ImCameraPreview()
    : viewportSize(0, 0)
{
}

void GameEngineEditor::ImCameraPreview::render(void* textureID)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Camera Preview");
        ImVec2 currentViewportSize = ImGui::GetContentRegionAvail();
        //framebuffer sizeo = 0會出錯
        if ((currentViewportSize.x > 0.0f) && (currentViewportSize.y > 0.0f) &&
            ((this->viewportSize.x != currentViewportSize.x) || (this->viewportSize.y != currentViewportSize.y)))
        {
            this->viewportSize = currentViewportSize;
        }
        ImGui::Image(textureID, currentViewportSize, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
    ImGui::PopStyleVar(1);
}
