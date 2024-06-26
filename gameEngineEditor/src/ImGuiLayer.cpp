#include "ImGuiLayer.h"
#include "imgui.h"
#include "Core/Platform.h"
#include "Event/OpenProjectEvent.h"
#include "Event/SaveProjectEvent.h"
#include "Event/EventDispatcher.h"
#include "Panel/ImDebugger.h"
#include "Event/Input.h"
#include "EditorColor.h"

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
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_TitleBg] = COLOR_TO_IMVEC4(GameEngineEditor::TitleBarColor);
    style.Colors[ImGuiCol_TitleBgActive] = COLOR_TO_IMVEC4(GameEngineEditor::TitleBarActiveColor);
    
    style.Colors[ImGuiCol_Tab] = COLOR_TO_IMVEC4(GameEngineEditor::TabColor);
    style.Colors[ImGuiCol_TabActive] = COLOR_TO_IMVEC4(GameEngineEditor::TabActiveColor);
    style.Colors[ImGuiCol_TabUnfocused] = COLOR_TO_IMVEC4(GameEngineEditor::TabUnfocusedColor);
    style.Colors[ImGuiCol_TabUnfocusedActive] = COLOR_TO_IMVEC4(GameEngineEditor::TabUnfocusedActiveColor);
    style.Colors[ImGuiCol_TabHovered] = COLOR_TO_IMVEC4(GameEngineEditor::TabHoveredColor);
    
    style.Colors[ImGuiCol_WindowBg] = COLOR_TO_IMVEC4(GameEngineEditor::WindowColor);

    style.Colors[ImGuiCol_FrameBg] = COLOR_TO_IMVEC4(GameEngineEditor::FrameColor);

    style.Colors[ImGuiCol_ButtonHovered] = COLOR_TO_IMVEC4(GameEngineEditor::ButtonHoveredColor);
    style.Colors[ImGuiCol_ButtonActive] = COLOR_TO_IMVEC4(GameEngineEditor::ButtonActiveColor);

    style.Colors[ImGuiCol_Header] = COLOR_TO_IMVEC4(GameEngineEditor::HeaderColor);
    style.Colors[ImGuiCol_HeaderActive] = COLOR_TO_IMVEC4(GameEngineEditor::HeaderActiveColor);
    style.Colors[ImGuiCol_HeaderHovered] = COLOR_TO_IMVEC4(GameEngineEditor::HeaderHoveredColor);

    this->contentBrowserPanel.begin();
}

void GameEngineEditor::ImGuiLayer::setScene(GameEngine::Scene* scene)
{
    this->scene = scene;
    this->sceneHierarchyPanel.setScene(this->scene);
}

void GameEngineEditor::ImGuiLayer::setSelectedEntityID(uint32_t entityID)
{
    this->sceneHierarchyPanel.setSelectedEntityID(entityID);
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
            if (ImGui::MenuItem("Open project", "Ctrl+O"))
            {
                std::string projectPath = GameEngineEditor::WindowsApi::openProjectFile(this->windowID);
                if (!projectPath.empty())
                {
                    GameEngineEditor::OpenProjectEvent openProjectEvent(projectPath);
                    GameEngine::EventDispatcher::trigger(&openProjectEvent);
                }
            }
            if (ImGui::MenuItem("Save project", "Ctrl+N"))
            {
                GameEngineEditor::SaveProjectEvent saveProjectEvent;
                GameEngine::EventDispatcher::trigger(&saveProjectEvent);
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

void GameEngineEditor::ImGuiLayer::renderCameraPreview(void* textureID, float aspectRatio)
{
    this->cameraPreview.render(textureID, aspectRatio);
}

void GameEngineEditor::ImGuiLayer::renderAllPanel(float fps)
{
    //第一次設定即可
    static bool defaultShowContentBrowser = true;

    this->sceneHierarchyPanel.render();
    this->propertiesPanel.render((entt::entity)this->sceneHierarchyPanel.getSelectedEntityID(), this->scene);
    this->contentBrowserPanel.render();
    this->terminal.render();
    if (this->isShowDebug)
        GameEngineEditor::ImDebugger::render(fps);

    if (defaultShowContentBrowser)
    {
        ImGui::SetWindowFocus("Content Browser");
        defaultShowContentBrowser = false;
    }
}

void GameEngineEditor::ImGuiLayer::setProjectRootPath(const std::string& rootPath)
{
    this->contentBrowserPanel.setRootPath(rootPath);
    this->propertiesPanel.setRootPath(rootPath);
}

void GameEngineEditor::ImGuiLayer::eventHandle()
{
    //shortcut
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_LCTRL) && GameEngine::Input::isKeyPressed(GameEngine::Key_O))
    {
        std::string projectPath = GameEngineEditor::WindowsApi::openProjectFile(this->windowID);
        if (!projectPath.empty())
        {
            GameEngineEditor::OpenProjectEvent openProjectEvent(projectPath);
            GameEngine::EventDispatcher::trigger(&openProjectEvent);
        }
    }
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_LCTRL) && GameEngine::Input::isKeyPressed(GameEngine::Key_S))
    {
        GameEngineEditor::SaveProjectEvent saveProjectEvent;
        GameEngine::EventDispatcher::trigger(&saveProjectEvent);
    }
}

#if USE_WINDOWS
void GameEngineEditor::ImGuiLayer::setWindowID(HWND windowID)
{
    this->windowID = windowID;
}
#endif