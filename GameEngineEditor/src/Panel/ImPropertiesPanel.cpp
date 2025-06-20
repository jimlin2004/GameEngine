#include "Panel/ImPropertiesPanel.h"

#include "Opengl/Texture.h"
#include "Component/Component.h"
#include "Actor/Actor.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "EditorColor.h"
#include "Platform/Windows/WindowsApi.h"
#include "glm/gtc/type_ptr.hpp"
#include <cstring>

void GameEngineEditor::ImPropertiesPanel::setRootPath(const std::filesystem::path &newPath)
{
    this->rootPath = newPath;
}

template<class ComponentType, class Func>
static void renderComponent(const std::string& label, GameEngine::Actor& actor, bool canRemove, Func func)
{
    static ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_OpenOnArrow;
    if (actor.hasComponent<ComponentType>())
    {
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_Header, GameEngineEditor::PropertiesTreeNodeColor);
        bool needToRemoveComponent = false;
        if (ImGui::TreeNodeEx(label.c_str(), flags, label.c_str()))
        {
            if (canRemove)
            {
                float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
                float contentWidth = ImGui::GetContentRegionAvail().x;
                ImGui::SameLine(contentWidth - lineHeight * 0.5f);
                ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::PropertiesTreeNodeColor);
                if (ImGui::Button("x", {lineHeight, lineHeight}))
                {
                    needToRemoveComponent = true;
                }
                ImGui::PopStyleColor(1);
            }
            func(actor.getComponent<ComponentType>());
            ImGui::TreePop();
        }
        ImGui::PopStyleColor(1);
        ImGui::PopStyleVar(1);
    
        if (needToRemoveComponent)
            actor.removeComponent<ComponentType>();
    }
}

void renderEdit3(const std::string& label, glm::vec3& values)
{
    ImGui::Text(label.c_str());
    ImGui::BeginTable("##Edit3-Table", 6, ImGuiTableFlags_NoPadInnerX);
        ImGui::TableSetupColumn("##Column1", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("##Column2", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("##Column3", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("##Column4", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("##Column5", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("##Column6", ImGuiTableColumnFlags_WidthStretch);

        ImGui::PushID(label.c_str());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 5});

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::xAxisColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, GameEngineEditor::xAxisHintColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, GameEngineEditor::xAxisHintColor);
        if (ImGui::Button("X"))
            values.x = 0.0f;
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-1);
        ImGui::DragFloat("##X", &values.x, 0.1, 0.0f, 0.0f);
        ImGui::PopStyleColor(3);
        
        ImGui::TableNextColumn();
        ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::yAxisColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, GameEngineEditor::yAxisHintColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, GameEngineEditor::yAxisHintColor);
        if (ImGui::Button("Y"))
            values.y = 0.0f;
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-1);
        ImGui::DragFloat("##Y", &values.y, 0.1, 0.0f, 0.0f);
        ImGui::PopStyleColor(3);
        
        ImGui::TableNextColumn();
        ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::zAxisColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, GameEngineEditor::zAxisHintColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, GameEngineEditor::zAxisHintColor);
        if (ImGui::Button("Z"))
            values.z = 0.0f;
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-1);
        ImGui::DragFloat("##Z", &values.z, 0.1, 0.0f, 0.0f);
        ImGui::PopStyleColor(3);

        ImGui::PopStyleVar(1);
        ImGui::PopID();
    ImGui::EndTable();
}

void renderEdit2(const std::string& label, glm::vec2& values)
{
    ImGui::Text(label.c_str());
    ImGui::BeginTable("##Edit2-Table", 4, ImGuiTableFlags_NoPadInnerX);
        ImGui::TableSetupColumn("##Column1", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("##Column2", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("##Column3", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("##Column4", ImGuiTableColumnFlags_WidthStretch);

        ImGui::PushID(label.c_str());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 5});

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::xAxisColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, GameEngineEditor::xAxisHintColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, GameEngineEditor::xAxisHintColor);
        if (ImGui::Button("X"))
            values.x = 0.0f;
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-1);
        ImGui::DragFloat("##X", &values.x, 0.1, 0.0f, 0.0f);
        ImGui::PopStyleColor(3);
        
        ImGui::TableNextColumn();
        ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::yAxisColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, GameEngineEditor::yAxisHintColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, GameEngineEditor::yAxisHintColor);
        if (ImGui::Button("Y"))
            values.y = 0.0f;
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-1);
        ImGui::DragFloat("##Y", &values.y, 0.1, 0.0f, 0.0f);
        ImGui::PopStyleColor(3);

        ImGui::PopStyleVar(1);
        ImGui::PopID();
    ImGui::EndTable();
}

inline void renderLeftLabel(const char* label)
{
    ImGui::AlignTextToFramePadding();
    ImGui::Text(label);
    ImGui::SameLine();
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
            renderAddComponentItem<GameEngine::ScriptComponent>("Script", actor);
            renderAddComponentItem<GameEngine::Rigidbody2DComponent>("Rigidbody2D", actor);
            renderAddComponentItem<GameEngine::BoxCollider2DComponent>("BoxCollider2D", actor);
            ImGui::EndPopup();
        }

        if (actor.hasComponent<GameEngine::TagComponent>())
        {
            static char tagBuffer[256];
            static size_t tagBufferSize = sizeof(tagBuffer);
            GameEngine::TagComponent& tagComponent = actor.getComponent<GameEngine::TagComponent>();
            strncpy(tagBuffer, tagComponent.tagName.c_str(), tagBufferSize);
            renderLeftLabel("Tag");
            ImGui::SetNextItemWidth(-1);
            if (ImGui::InputText("##Tag", tagBuffer, tagBufferSize))
            {
                tagComponent.tagName = tagBuffer;
            }
        }

        renderComponent<GameEngine::TransformComponent>("Transform", actor, false, [](GameEngine::TransformComponent& component) {
            renderEdit3("Position", component.translation);
            glm::vec3 rotation = glm::degrees(component.rotation);
            renderEdit3("Rotation", rotation);
            component.rotation = glm::radians(rotation);
            renderEdit3("Scale", component.scale);
        });
        renderComponent<GameEngine::MeshComponent>("Mesh", actor, false, [](GameEngine::MeshComponent& component) {
            renderLeftLabel("Color");
            ImGui::SetNextItemWidth(-1);
            ImGui::ColorEdit4("##Color", glm::value_ptr(component.color));
            ImGui::Text("Texture");
            void* texturePtr;
            if (component.texture == nullptr)
                texturePtr = 0;
            else
                texturePtr = reinterpret_cast<void*>(component.texture->getTextureID());
            ImGui::Image(texturePtr, {50.0f, 50.0f}, {0, 1}, {1, 0});
        });
        renderComponent<GameEngine::CameraComponent>("Camera", actor, true, [](GameEngine::CameraComponent& component) {
            renderLeftLabel("Primary Camera");
            ImGui::Checkbox("##Primary Camera", &component.primary);
            static float orthographicSize, orthographicNear, orthographicFar, aspectRatio;
            static bool needToUpdate = false;
            orthographicSize = component.camera.getOrthographicSize();
            orthographicNear = component.camera.getOrthographicNear();
            orthographicFar = component.camera.getOrthographicFar();
            aspectRatio = component.camera.getAspectRatio();
            
            ImGui::BeginTable("##Camera-table", 2);
                ImGui::TableSetupColumn("##Column1", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("##Column2", ImGuiTableColumnFlags_WidthStretch);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                renderLeftLabel("Orthographic Size");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                if (ImGui::DragFloat("##Orthographic Size", &orthographicSize, 0.1f))
                    needToUpdate = true;

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                renderLeftLabel("Orthographic Near");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                if (ImGui::DragFloat("##Orthographic Near", &orthographicNear, 0.1f))
                    needToUpdate = true;

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                renderLeftLabel("Orthographic Far");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                if (ImGui::DragFloat("##Orthographic Far", &orthographicFar, 0.1f))
                    needToUpdate = true;

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                renderLeftLabel("Aspect Ratio");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                if (ImGui::DragFloat("##Aspect Ratio", &aspectRatio, 0.01f))
                    component.camera.setAspectRation(aspectRatio);
                if (needToUpdate)
                    component.camera.setOrthographic(orthographicSize, orthographicNear, orthographicFar);
            ImGui::EndTable();
        });
        renderComponent<GameEngine::ScriptComponent>("Script", actor, true, [this](GameEngine::ScriptComponent& component) {
            static char inputBuffer[128];
            static size_t inputBufferSize = sizeof(inputBuffer);
            
            if (!component.scriptPath.empty())
            {
                strncpy(inputBuffer, std::filesystem::path(component.scriptPath).filename().generic_string().c_str(), inputBufferSize);
            }
            else
                inputBuffer[0] = '\0';
            
            renderLeftLabel("Script");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(-1);
            ImGui::InputText("##input-script", inputBuffer, inputBufferSize, ImGuiInputTextFlags_ReadOnly);
            
            ImVec2 panelSize = ImGui::GetContentRegionAvail();
            ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::AddCompnentButtonColor);
            if (ImGui::Button("Selected Script", {panelSize.x, 0}))
            {
                std::string pathStr = GameEngineEditor::WindowsApi::openFile(NULL, "lua script(*.lua)\0*.lua\0");
                std::filesystem::path scriptPath(pathStr);
                strncpy(inputBuffer, scriptPath.filename().u8string().c_str(), inputBufferSize);
                component.scriptPath = std::filesystem::relative(scriptPath, this->rootPath).generic_string();
            }
            ImGui::PopStyleColor(1);
        });
        renderComponent<GameEngine::Rigidbody2DComponent>("Rigidbody2D", actor, true, [](GameEngine::Rigidbody2DComponent& component) {
            static const char* types[] = { "Static", "Dynamic", "Kinematic" };
            static int type = -1;
            type = (int)component.type;
            renderLeftLabel("Type");
            ImGui::SetNextItemWidth(-1);
            if (ImGui::Combo("##Type", &type, types, IM_ARRAYSIZE(types)))
            {
                component.type = (GameEngine::Rigidbody2DComponent::BodyType)type;
            }
            renderLeftLabel("Fix Rotation");
            ImGui::Checkbox("##Fix Rotation", &component.fixedRotation);
        });
        renderComponent<GameEngine::BoxCollider2DComponent>("BoxCollider2D", actor, true, [](GameEngine::BoxCollider2DComponent& component) {
            renderEdit2("Offset", component.offset);
            renderEdit2("Size", component.size);
            ImGui::BeginTable("##BoxCollider2D-table", 2);
                ImGui::TableSetupColumn("##Column1", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("##Column2", ImGuiTableColumnFlags_WidthStretch);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                renderLeftLabel("Density");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                ImGui::DragFloat("##Density", &component.density, 0.1f);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                renderLeftLabel("Friction");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                ImGui::DragFloat("##Friction", &component.friction, 0.1f);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                renderLeftLabel("Restitution");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                ImGui::DragFloat("##Restitution", &component.restitution, 0.1f);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                renderLeftLabel("Restitution Threshold");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(-1);
                ImGui::DragFloat("##Restitution Threshold", &component.restitutionThreshold, 0.1f);
            ImGui::EndTable();
        });
    }
    ImGui::End();
}