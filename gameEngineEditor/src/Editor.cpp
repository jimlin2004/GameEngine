#include "Editor.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Math/Math.h"
#include "Core/CameraController.h"
#include "Opengl/TextureManager.h"
#include "Event/Input.h"
#include "ImGuiLayer.h"

#include <filesystem>

GameEngineEditor::Editor::Editor(const char* title, int width, int height)
    : title(title)
    , screenWidth(width)
    , screenHeight(height)
    , lastFrameTime(0)
    , viewportSize(width, height)
    , editorCamera((width / (float)(height)))
    , frameBuffer(nullptr)
    , running(false)
    , isFocusOnViewport(false)
    , sceneState(GameEngineEditor::SceneState::Edit)
{
}

GameEngineEditor::Editor::~Editor()
{
}

bool GameEngineEditor::Editor::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        GameEngine::ConsoleApi::log("[Error] SDL Init Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    this->window = SDL_CreateWindow(this->title, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        this->screenWidth,
        this->screenHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!this->window)
    {
        GameEngine::ConsoleApi::log("[Error] Create Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    
    this->GLContext = SDL_GL_CreateContext(this->window);
    if (!this->GLContext)
    {
        GameEngine::ConsoleApi::log("[Error] Create Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    GameEngine::ConsoleApi::log("[Info] Create windows success.\n");
    SDL_GL_MakeCurrent(this->window, this->GLContext);
    if (glewInit() != GLEW_OK)
    {
        GameEngine::ConsoleApi::log("Init glew error\n");
        return false;
    }
    GameEngine::ConsoleApi::log("[Info] OpenGL init success.\n");
    SDL_GL_SetSwapInterval(1);
    return true;
}

bool GameEngineEditor::Editor::initGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    return true;
}

bool GameEngineEditor::Editor::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(this->window, this->GLContext);
    ImGui_ImplOpenGL3_Init("#version 400 core");

    return true;
}

bool GameEngineEditor::Editor::initAll()
{
    bool result = this->initSDL() && this->initGL() && this->initImGui();
    if (!result)
        return false;
    this->init();
    return true;
}

void GameEngineEditor::Editor::init()
{
    GameEngine::Renderer::init();
}

void GameEngineEditor::Editor::update(float deltaTime)
{
}

void GameEngineEditor::Editor::render()
{
    static ImGuiIO& io = ImGui::GetIO();

    // bool snap = GameEngine::Input::isKeyPressed(GameEngine::Key_LCTRL);
    // float snapValue = (this->gizmoOperation == ImGuizmo::ROTATE) ? 45.0f : 10.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(this->window);
    ImGui::NewFrame();
    // ImGuizmo::BeginFrame();

    GameEngineEditor::ImGuiLayer::renderDockspace();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    // ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    // ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
    // ImGui::SetNextWindowSize(io.DisplaySize);
    // ImGui::SetNextWindowPos({0, 0});
    // ImGui::Begin("viewport", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
    //     | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    ImGui::Begin("viewport", NULL, ImGuiWindowFlags_NoTitleBar);
    {
        this->isFocusOnViewport = ImGui::IsWindowFocused();

        ImVec2 currentViewportSize = ImGui::GetContentRegionAvail();
        if ((this->viewportSize.x != currentViewportSize.x) || (this->viewportSize.y != currentViewportSize.y))
        {
            this->viewportSize = currentViewportSize;
            this->editorCamera.resize(this->viewportSize.x, this->viewportSize.y);
            this->frameBuffer->resize(this->viewportSize.x, this->viewportSize.y);
        }
        uint32_t textureId = this->frameBuffer->getColorAttachmentRendererID();
        ImGui::Image((ImTextureID)textureId, currentViewportSize, ImVec2(0, 1), ImVec2(1, 0));
    
        // if (this->mainWindowExportDataPtr)
        // {
        //     if (this->hoveredActor)
        //     {
        //         this->mainWindowExportDataPtr->outlineTreeWidget->setSelectedEntity(
        //             this->mainWindowExportDataPtr->actorCollection->getItemByEntityID((entt::entity)this->hoveredActor.getID())
        //         );
        //         this->hoveredActor.setEntityID(entt::null);
        //     }
        //     entt::entity entityId = this->mainWindowExportDataPtr->outlineTreeWidget->getSelectedEntity();
        //     if (entityId != entt::null)
        //     {
        //         this->imguizmoVisible = true;
        //         ImGuizmo::SetOrthographic(true);
        //         ImGuizmo::SetDrawlist();
        //         ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
        //         const glm::mat4& cameraProjection = this->editorCamera.getProjection();
        //         glm::mat4 cameraView = glm::inverse(this->editorCamera.getTransform());
        //         GameEngine::TransformComponent& transformComponent = GameEngine::globalScene->queryActorComponent<GameEngine::TransformComponent>(entityId);
        //         glm::mat4 transform = transformComponent.getTransform();
                
        //         float snapValues[3] = { snapValue, snapValue, snapValue };
                
        //         ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), 
        //             this->gizmoOperation, ImGuizmo::MODE::LOCAL, glm::value_ptr(transform)
        //             , nullptr, (snap) ? snapValues : nullptr
        //         );
        //         if (ImGuizmo::IsUsing())
        //         {
        //             glm::vec3 translation, rotation, scale;
        //             GameEngine::Math::decomposeTransform(transform, translation, rotation, scale);
        //             transformComponent.translation = translation;
        //             glm::vec3 deltaRotation = rotation - transformComponent.rotation;
        //             transformComponent.rotation += deltaRotation; //解決萬向鎖問題
        //             transformComponent.scale = scale;
        //         }
        //     }
        //     else
        //         this->imguizmoVisible = false;
        // }
    }
    ImGui::End();
    ImGui::PopStyleVar(1);
    // ImGui::PopStyleVar(3);
    GameEngineEditor::ImGuiLayer::renderAllPanel();
    ImGui::Render();

    GameEngine::GEngine->textureManager->processCreateTextureTasks();

    this->frameBuffer->bind();
    GameEngine::Renderer::begin((*GameEngine::cameraController->getCamera()), GameEngine::cameraController->getTransform());
        GameEngine::Renderer::drawQuad({0, 0, 0}, {1, 1}, {0.5, 1, 1, 1});
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GameEngine::globalScene->render();
        frameBuffer->clearAttachment(1, -1);
    GameEngine::Renderer::close();

    // int mx, my;
    // GameEngine::Input::getMousePosition(&mx, &my);
    // my = io.DisplaySize.y - my;
    // if (mx >= 0 && mx < io.DisplaySize.x && my >= 0 && my < io.DisplaySize.y)
    // {
    //     int pixelData = frameBuffer->readPixel(1, mx, my);
    //     if (GameEngine::Input::isMouseButtonPressed(GameEngine::Mouse_BUTTON_LEFT))
    //     {
    //         if (!ImGuizmo::IsOver() || !this->imguizmoVisible)
    //         {
    //             this->hoveredActor.setEntityID((pixelData == -1) ? entt::null : (entt::entity)pixelData);
    //             if (pixelData == -1)
    //                 this->mainWindowExportDataPtr->outlineTreeWidget->setSelectedEntity(nullptr);
    //         }
    //     }
    // }
    
    this->frameBuffer->unbind();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GameEngineEditor::Editor::gameEventHandle()
{
    //清除SDL鍵盤事件
    // SDL_ResetKeyboard();

    static ImGuiIO& io = ImGui::GetIO();
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&this->event);
        switch (this->event.type)
        {
            case SDL_QUIT:
                this->running = false;
                break;
            case SDL_MOUSEWHEEL:
                if (this->isFocusOnViewport)
                    this->editorCamera.onScrollWheel(event.wheel.preciseX, event.wheel.preciseY);
                break;
            default:
                break;
        }
    }
}

void GameEngineEditor::Editor::begin()
{
    GameEngine::FrameBufferSpecification spec;
    spec.width = this->viewportSize.x,
    spec.height = this->viewportSize.y,
    spec.attachments = {
        GameEngine::FrameBufferTextureFormat::RGBA8,
        GameEngine::FrameBufferTextureFormat::RED_INTEGER, //mouse picking
        GameEngine::FrameBufferTextureFormat::Depth
    };
    this->frameBuffer = new GameEngine::FrameBuffer(spec);
    GameEngine::cameraController->setViewTarget(&this->editorCamera, &this->editorCamera.transformComponent);
}

void GameEngineEditor::Editor::logBuildInfo()
{
}

void GameEngineEditor::Editor::updateEditorCamera(float deltaTime)
{
    constexpr static int speed = 5;

    if (this->isFocusOnViewport)
    {
        if (GameEngine::Input::isKeyPressed(GameEngine::Key_D))
            this->editorCamera.setX(this->editorCamera.getX() + (speed * deltaTime));
        if (GameEngine::Input::isKeyPressed(GameEngine::Key_A))
            this->editorCamera.setX(this->editorCamera.getX() - (speed * deltaTime));
        if (GameEngine::Input::isKeyPressed(GameEngine::Key_W))
            this->editorCamera.setY(this->editorCamera.getY() + (speed * deltaTime));
        if (GameEngine::Input::isKeyPressed(GameEngine::Key_S))
            this->editorCamera.setY(this->editorCamera.getY() - (speed * deltaTime));
    }
}

void GameEngineEditor::Editor::start()
{
    this->begin();
    this->running = true;
    uint64_t time = SDL_GetPerformanceCounter();
    while (this->running)
    {
        this->lastFrameTime = time;
        time = SDL_GetPerformanceCounter();
        this->timestep = ((time - this->lastFrameTime) * 1000.0f / SDL_GetPerformanceFrequency()) * 0.001f;
        this->gameEventHandle();

        if (this->sceneState == GameEngineEditor::SceneState::Edit)
        {
            this->updateEditorCamera(this->timestep);
        }

        this->update(this->timestep);
        this->render();
        SDL_GL_SwapWindow(this->window);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
