#include "Panel/ImPropertiesPanel.h"

#include "Component/Component.h"
#include "Actor/Actor.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "EditorColor.h"

#include "glm/gtc/type_ptr.hpp"
#include <cstring>

template<class ComponentType, class Func>
static void renderComponent(const std::string& label, GameEngine::Actor& actor, Func func)
{
    static ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
    if (actor.hasComponent<ComponentType>())
    {
        ImGui::PushStyleColor(ImGuiCol_Header, GameEngineEditor::PropertiesTreeNodeColor);
        if (ImGui::TreeNodeEx(label.c_str(), flags, label.c_str()))
        {
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
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, GameEngineEditor::xAxisHintColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, GameEngineEditor::xAxisHintColor);
    if (ImGui::Button("X"))
        values.x = 0.0f;
    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1, 0.0f, 0.0f);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PopStyleColor(3);
    
    ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::yAxisColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, GameEngineEditor::yAxisHintColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, GameEngineEditor::yAxisHintColor);
    if (ImGui::Button("Y"))
        values.y = 0.0f;
    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1, 0.0f, 0.0f);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PopStyleColor(3);
    
    ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::zAxisColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, GameEngineEditor::zAxisHintColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, GameEngineEditor::zAxisHintColor);
    if (ImGui::Button("Z"))
        values.z = 0.0f;
    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1, 0.0f, 0.0f);
    ImGui::PopItemWidth();
    ImGui::PopStyleColor(3);

    ImGui::PopStyleVar(1);
    ImGui::PopID();
    // ImGui::Columns(1);
}

template<class ComponentType>
void renderAddComponentItem(const std::string& label, GameEngine::Actor& actor)
{
    if (!actor)
        return;
    if (!actor.hasComponent<ComponentType>())
    {
        if (ImGui::MenuItem(label.c_str()))
        {
            actor.addComponent<ComponentType>();
            ImGui::CloseCurrentPopup();
        }
    }
}

void GameEngineEditor::ImPropertiesPanel::render(entt::entity entityID, GameEngine::Scene* scene)
{
    GameEngine::Actor actor(entityID, scene);
    ImGui::Begin("Properties");
    if (actor)
    {
        ImVec2 panelSize = ImGui::GetContentRegionAvail();
        ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::AddCompnentButtonColor);
        if (ImGui::Button("Add Component", {panelSize.x, 0}))
        {
            ImGui::OpenPopup("##AddComponent");
        }
        ImGui::PopStyleColor(1);
        if (ImGui::BeginPopup("##AddComponent"))
        {
            renderAddComponentItem<GameEngine::TransformComponent>("Transform", actor);
            renderAddComponentItem<GameEngine::MeshComponent>("Mesh", actor);
            renderAddComponentItem<GameEngine::CameraComponent>("Camera", actor);
            ImGui::EndPopup();
        }

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

        renderComponent<GameEngine::TransformComponent>("Transform", actor, [](GameEngine::TransformComponent& component) {
            renderEdit3("Position", component.translation);
            glm::vec3 rotation = glm::degrees(component.rotation);
            renderEdit3("Rotation", rotation);
            component.rotation = glm::radians(rotation);
            renderEdit3("Scale", component.scale);
        });
        renderComponent<GameEngine::MeshComponent>("Mesh", actor, [](GameEngine::MeshComponent& component) {
            ImGui::ColorEdit4("Color", glm::value_ptr(component.color));
        });
        renderComponent<GameEngine::CameraComponent>("Camera", actor, [](GameEngine::CameraComponent& component) {
            ImGui::Checkbox("Primary camera", &component.primary);
            static float orthographicSize, orthographicNear, orthographicFar, aspectRatio;
            static bool needToUpdate = false;
            orthographicSize = component.camera.getOrthographicSize();
            orthographicNear = component.camera.getOrthographicNear();
            orthographicFar = component.camera.getOrthographicFar();
            aspectRatio = component.camera.getAspectRatio();
            if (ImGui::DragFloat("Orthographic Size", &orthographicSize, 0.1f))
                needToUpdate = true;
            if (ImGui::DragFloat("Orthographic Near", &orthographicNear, 0.1f))
                needToUpdate = true;
            if (ImGui::DragFloat("Orthographic Far", &orthographicFar, 0.1f))
                needToUpdate = true;
            if (ImGui::DragFloat("Aspect Ratio", &aspectRatio, 0.01f))
                component.camera.setAspectRation(aspectRatio);
            if (needToUpdate)
                component.camera.setOrthographic(orthographicSize, orthographicNear, orthographicFar);
        });
    }
    ImGui::End();
}