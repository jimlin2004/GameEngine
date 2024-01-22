#include "Panel/ImSceneHierarchyPanel.h"
#include "imgui/imgui.h"

#include "Actor/Actor.h"
#include "Component/Component.h"
#include "Event/EventDispatcher.h"
#include "Event/ImTreeNodeClickEvent.h"
#include "EditorColor.h"

GameEngineEditor::ImSceneHierarchyPanel::ImSceneHierarchyPanel()
    : scene(nullptr)
    , selectedEntity(entt::null)
{
}

void GameEngineEditor::ImSceneHierarchyPanel::setScene(GameEngine::Scene* scene)
{
    this->scene = scene;
}
void GameEngineEditor::ImSceneHierarchyPanel::render()
{
    ImGui::Begin("Scene Hierarchy");
        if (this->scene != nullptr)
        {
            this->scene->registry.each([&](entt::entity entityID) {
                GameEngine::Actor actor = {entityID, this->scene};
                this->renderActorNode(actor);
            });
        }
    ImGui::End();
}

void GameEngineEditor::ImSceneHierarchyPanel::setSelectedEntityID(uint32_t entityID)
{
    this->selectedEntity = entityID;
}

void GameEngineEditor::ImSceneHierarchyPanel::renderActorNode(GameEngine::Actor &actor)
{
    GameEngine::TagComponent& tagComponent = actor.getComponent<GameEngine::TagComponent>();
    ImGuiTreeNodeFlags flags = ((this->selectedEntity == actor.getID()) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    bool opened = ImGui::TreeNodeEx((void*)((uint64_t)actor.getID()), flags, tagComponent.tagName.c_str());
    
    if (ImGui::IsItemClicked())
    {
        this->selectedEntity = actor.getID();
        GameEngineEditor::ImTreeNodeClickEvent event((this->selectedEntity));
        GameEngine::EventDispatcher::trigger(&event);
    }
    
    if (opened)
        ImGui::TreePop();
}
