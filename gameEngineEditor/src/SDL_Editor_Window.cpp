#include "SDL_Editor_Window.h"
#include "Event/Input.h"
#include <winuser.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Math/Math.h"

SDL_Editor_Window::SDL_Editor_Window(const char* title, int width, int height)
    : GameBase(title, width, height)
    , isFocusOnSDLPtr(nullptr)
    , outlineTreeWidgetPtr(nullptr)
    , viewportSize(width, height)
    , gizmoOperation(ImGuizmo::OPERATION::TRANSLATE)
    , frameBuffer(nullptr)
{
}

SDL_Editor_Window::~SDL_Editor_Window()
{
}

void SDL_Editor_Window::init()
{
    GameEngine::Renderer::init();
}

bool SDL_Editor_Window::initSDL()
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
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
        // SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
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

bool SDL_Editor_Window::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(this->window, this->GLContext);
    ImGui_ImplOpenGL3_Init("#version 400 core");

    return true;
}

void SDL_Editor_Window::startGame()
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
        this->updateEditorCamera(this->timestep);
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

void SDL_Editor_Window::begin()
{   
    GameEngine::FrameBufferSpecification spec;
    spec.width = this->viewportSize.x,
    spec.height = this->viewportSize.y,
    spec.attachments = {
        GameEngine::FrameBufferTextureFormat::RGBA8,
        GameEngine::FrameBufferTextureFormat::Depth
    };
    this->frameBuffer = new GameEngine::FrameBuffer(spec);
}

void SDL_Editor_Window::update(float deltaTime)
{
}

void SDL_Editor_Window::render()
{
    
    static ImGuiIO& io = ImGui::GetIO();

    bool snap = GameEngine::Input::isKeyPressed(GameEngine::Key_LCTRL);
    float snapValue = (this->gizmoOperation == ImGuizmo::ROTATE) ? 45.0f : 10.0f;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(this->window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("viewport", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    {
        ImVec2 currentViewportSize = ImGui::GetContentRegionAvail();
        if ((this->viewportSize.x != currentViewportSize.x) || (this->viewportSize.y != currentViewportSize.y))
        {
            this->viewportSize = currentViewportSize;
            GameEngine::cameraController->getCamera()->setProjectionMatrix(0.0, this->viewportSize.x, 0.0, this->viewportSize.y);
            this->frameBuffer->resize(this->viewportSize.x, this->viewportSize.y);
        }
        uint32_t textureId = this->frameBuffer->getColorAttachmentRendererID();
        ImGui::Image((ImTextureID)textureId, currentViewportSize, ImVec2(0, 1), ImVec2(1, 0));
    
        if (this->outlineTreeWidgetPtr)
        {
            entt::entity entityId = this->outlineTreeWidgetPtr->getSelectedEntity();
            if (entityId != entt::null)
            {
                ImGuizmo::SetOrthographic(true);
                ImGuizmo::SetDrawlist();
                ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
                const glm::mat4& cameraProjection = GameEngine::cameraController->getCamera()->getProjectionMatrix();
                glm::mat4 cameraView = glm::inverse(GameEngine::cameraController->getTransform());
                GameEngine::TransformComponent& transformComponent = GameEngine::globalScene->queryActorComponent<GameEngine::TransformComponent>(entityId);
                glm::mat4 transform = transformComponent.getTransform();
                
                float snapValues[3] = { snapValue, snapValue, snapValue };
                
                ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), 
                    this->gizmoOperation, ImGuizmo::MODE::LOCAL, glm::value_ptr(transform)
                    , nullptr, (snap) ? snapValues : nullptr
                );
                if (ImGuizmo::IsUsing())
                {
                    glm::vec3 translation, rotation, scale;
                    GameEngine::Math::decomposeTransform(transform, translation, rotation, scale);
                    transformComponent.translation = translation;
                    glm::vec3 deltaRotation = rotation - transformComponent.rotation;
                    transformComponent.rotation += deltaRotation; //解決萬向鎖問題
                    transformComponent.scale = scale;
                }
            }
        }
    }
    ImGui::End();
    ImGui::PopStyleVar(3);
    ImGui::Render();
    this->frameBuffer->bind(); 
    GameEngine::Renderer::begin();
        GameEngine::Renderer::drawQuad({100.0f, 30.0f, 1.0f}, {50.0f, 50.0f}, {1.0, 1.0f, 1.0f, 1.0f});
        GameEngine::globalScene->render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //我不知道為什麼一定要
    GameEngine::Renderer::close();
    this->frameBuffer->unbind();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void SDL_Editor_Window::gameEventHandle()
{
    while (SDL_PollEvent(&this->event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        switch (this->event.type)
        {
            case SDL_QUIT:
                this->running = false;
                break;
            default:
                break;
        }
    }
    if (GameEngine::Input::isMouseButtonPressed(GameEngine::Mouse_BUTTON_LEFT))
    {
        if (*(this->isFocusOnSDLPtr) == false)
        {
            SDL_SysWMinfo wmInfo;
            SDL_VERSION(&wmInfo.version);
            SDL_GetWindowWMInfo(this->window, &wmInfo);
            SetFocus(wmInfo.info.win.window);
            *(this->isFocusOnSDLPtr) = true;
        }
    }
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_E))
        this->gizmoOperation = ImGuizmo::SCALE;
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_R))
        this->gizmoOperation = ImGuizmo::ROTATE;
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_G))
        this->gizmoOperation = ImGuizmo::TRANSLATE;
}

void SDL_Editor_Window::bindIsFocusOnSDL(bool *ptr)
{
    this->isFocusOnSDLPtr = ptr;
}

void SDL_Editor_Window::updateEditorCamera(float deltaTime)
{
    constexpr static int speed = 100;
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_D))
    {
        GameEngine::cameraController->moveCameraX(GameEngine::cameraController->getCameraX() + (speed * deltaTime));
    }
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_A))
    {
        GameEngine::cameraController->moveCameraX(GameEngine::cameraController->getCameraX() - (speed * deltaTime));
    }
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_W))
    {
        GameEngine::cameraController->moveCameraY(GameEngine::cameraController->getCameraY() + (speed * deltaTime));
    }
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_S))
    {
        GameEngine::cameraController->moveCameraY(GameEngine::cameraController->getCameraY() - (speed * deltaTime));
    }
}

void SDL_Editor_Window::bindOutlineTreeWidget(OutlineTreeWidget *ptr)
{
    this->outlineTreeWidgetPtr = ptr;
}
