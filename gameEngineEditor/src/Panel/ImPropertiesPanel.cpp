#include "Panel/ImPropertiesPanel.h"

#include "Component/Component.h"
#include "Actor/Actor.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "EditorColor.h"

#include "glm/gtc/type_ptr.hpp"
#include <cstring>

template<class ComponentType, class Func>
static void renderComponent(const std::string& label, GameEngine::Actor& actor, uint64_t& id, Func func)
{
    static ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
    if (actor.hasComponent<ComponentType>())
    {
        ImGui::PushStyleColor(ImGuiCol_Header, GameEngineEditor::PropertiesTreeNodeColor);
        if (ImGui::TreeNodeEx((void*)(id), flags, label.c_str()))
        {
            ++id;
            func(actor.getComponent<ComponentType>());
            ImGui::TreePop();
        }
        ImGui::PopStyleColor(1);
    }
}

void renderEdit3(const std::string& label, glm::vec3& values)
{
    ImGui::PushID(label.c_str());
    // ImGui::Columns(2);
    // ImGui::SetColumnWidth(0, 100.0f);
    ImGui::Text(label.c_str());
    // ImGui::NextColumn();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 5});
    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

    ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::xAxisColor);
    ImGui::Button("X");
    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1, 0.0f, 0.0f);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PopStyleColor(1);
    
    ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::yAxisColor);
    ImGui::Button("Y");
    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1, 0.0f, 0.0f);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PopStyleColor(1);
    
    ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::zAxisColor);
    ImGui::Button("Z");
    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1, 0.0f, 0.0f);
    ImGui::PopItemWidth();
    ImGui::PopStyleColor(1);

    ImGui::PopStyleVar(1);
    ImGui::PopID();
    // ImGui::Columns(1);
}

void GameEngineEditor::ImPropertiesPanel::render(entt::entity entityID, GameEngine::Scene* scene)
{
    GameEngine::Actor actor(entityID, scene);
    ImGui::Begin("Properties");
    if (actor)
    {
        uint64_t id = 1;
        if (actor.hasComponent<GameEngine::TagComponent>())
        {
            static char tagBuffer[256];
            static size_t tagBufferSize = sizeof(tagBuffer);
            GameEngine::TagComponent& tagComponent = actor.getComponent<GameEngine::TagComponent>();
            strncpy(tagBuffer, tagComponent.tagName.c_str(), tagBufferSize);
            if (ImGui::InputText("Tag", tagBuffer, tagBufferSize))
            {
                tagComponent.tagName = tagBuffer;
            }
        }

        renderComponent<GameEngine::TransformComponent>("Transform", actor, id, [](GameEngine::TransformComponent& component) {
            renderEdit3("Position", component.translation);
            glm::vec3 rotation = glm::degrees(component.rotation);
            renderEdit3("Rotation", rotation);
            component.rotation = glm::radians(rotation);
            renderEdit3("Scale", component.scale);
        });
        renderComponent<GameEngine::MeshComponent>("Mesh", actor, id, [](GameEngine::MeshComponent& component) {
            ImGui::ColorEdit4("Color", glm::value_ptr(component.color));
        });
        renderComponent<GameEngine::CameraComponent>("Camera", actor, id, [](GameEngine::CameraComponent& component) {
            ImGui::Checkbox("Primary camera", &component.primary);
        });
    }
    ImGui::End();
}