#include "ImTerminal.h"

#include "imgui/imgui.h"
#include <string>

void GameEngineEditor::ImTerminal::render()
{
    ImGui::Begin("Terminal");
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4{0, 0, 0, 1});
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4{255, 221, 0, 1});
        ImGui::PushItemWidth(-1);
        ImGui::InputText("##input_terminal", this->inputBuffer, this->inputBufferSize);
        ImGui::PopItemWidth();
        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar(1);

        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4{255, 221, 0, 1});
        ImGui::BeginChild("##terminal_body", ImVec2{0, 0}, ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::EndChild();
        ImGui::PopStyleColor(1);
    ImGui::End();
}