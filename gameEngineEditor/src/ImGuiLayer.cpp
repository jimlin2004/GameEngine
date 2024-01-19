#include "ImGuiLayer.h"
#include "imgui/imgui.h"
#include "Core/Platform.h"
#include "Event/OpenProjectEvent.h"
#include "Event/EventDispatcher.h"
#include "Panel/ImDebugger.h"

#if USE_WINDOWS
    #include "Platform/Windows/WindowsApi.h"
#endif

GameEngineEditor::ImGuiLayer::ImGuiLayer()
    : isShowDebug(false)
{
}

GameEngineEditor::ImGuiLayer::~ImGuiLayer()
{
}

void GameEngineEditor::ImGuiLayer::setup()
{
    
}

void GameEngineEditor::ImGuiLayer::setScene(GameEngine::Scene* scene)
{
    this->scene = scene;
    this->sceneHierarchyPanel.setScene(this->scene);
}

void GameEngineEditor::ImGuiLayer::setSelectedEntity(uint32_t entityID)
{
    this->sceneHierarchyPanel.setSelectedEntity(entityID);
}

void GameEngineEditor::ImGuiLayer::renderDockspace()
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", NULL, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open project"))
            {
                GameEngineEditor::OpenProjectEvent openProjectEvent(std::string(GameEngineEditor::WindowsApi::openProjectFile()));
                GameEngine::EventDispatcher::trigger(&openProjectEvent);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Debug"))
        {
            ImGui::Checkbox("Show debug", &this->isShowDebug);
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
}

void GameEngineEditor::ImGuiLayer::renderObjectInformation()
{
    static char buffer[512];
    ImGui::Begin("Object Information");
        ImGui::InputText("Test", buffer, 512);
    ImGui::End();
}

void GameEngineEditor::ImGuiLayer::renderContentPanel()
{
    ImGui::Begin("Content panel");
    ImGui::End();
}

void GameEngineEditor::ImGuiLayer::renderAllPanel(float fps)
{
    ImGuiLayer::renderObjectInformation();
    this->sceneHierarchyPanel.render();
    ImGuiLayer::renderContentPanel();
    this->terminal.render();
    if (this->isShowDebug)
        GameEngineEditor::ImDebugger::render(fps);
}