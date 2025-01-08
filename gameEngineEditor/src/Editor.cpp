#include "Editor.h"

#include "GameEngineAPI/ConsoleApi.h"
#include "GameEngineAPI/GameEngineAPI.h"
#include "Render/Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Math/Math.h"
#include "Core/CameraController.h"
#include "Opengl/TextureManager.h"
#include "Event/Input.h"
#include "Event/EventDispatcher.h"
#include "Event/OpenProjectEvent.h"
#include "Event/ImTreeNodeClickEvent.h"
#include "Scene/SceneSerializer.h"
#include "SDLFileParser.h"
#include "ImGuiLayer.h"
#include "EditorColor.h"

#include <filesystem>

//Script
#include "Script/Event/ScriptEventDispatcher.h"
#include "Script/Event/KeyDownEvent.h"
#include "Script/Event/KeyUpEvent.h"

#include "Core/Platform.h"
#if USE_WINDOWS
    #include <windows.h>
#endif

GameEngineEditor::Editor::Editor(const char* title, int width, int height)
    : title(title)
    , screenWidth(width)
    , screenHeight(height)
    , lastFrameTime(0)
    , cameraPreviewSize(200, 200)
    , viewportSize(width, height)   
    , editorCamera((width / (float)(height)))
    , gizmoOperation(ImGuizmo::OPERATION::TRANSLATE)
    , viewportFrameBuffer(nullptr)
    , cameraViewFrameBuffer(nullptr)
    , running(false)
    , isFocusOnViewport(false)
    , sceneState(GameEngineEditor::SceneState::Edit)
    , needToStopScene(false)
    , needToStartScene(false)
    , editorScene(nullptr)
    , activeScene(new GameEngine::Scene())
{
    this->selectedActor.setEntityID(entt::null);
    this->selectedActor.bindScene(this->activeScene);
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
    this->initNative();
    this->init();
    return true;
}

void GameEngineEditor::Editor::init()
{
    GameEngine::Renderer::init();
}

float GameEngineEditor::Editor::getWindowDpiScale(SDL_Window* window)
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    if (displayIndex < 0)
    {
        //Error處理(還沒做)
        return 1.0f; //回傳默認縮放比例
    }
    float ddpi, hdpi, vdpi;
    if (SDL_GetDisplayDPI(displayIndex, &ddpi, &hdpi, &vdpi) == 0)
    {
        return ddpi / 96.0f; //96是標準DPI
    }
    return 1.0f; //回傳默認縮放比例
}

void GameEngineEditor::Editor::begin()
{
    // 調整DPI
    float dpiScale = this->getWindowDpiScale(this->window);
    ImGui::GetIO().FontGlobalScale = dpiScale;
    // ImGuiStyle& style = ImGui::GetStyle();
    // style.ScaleAllSizes(dpiScale);

    this->playBtnIconTexture = new GameEngine::Texture();
    this->playBtnIconTexture->load("./assets/texture/playButton.png", GL_NEAREST);
    this->stopBtnIconTexture = new GameEngine::Texture();
    this->stopBtnIconTexture->load("./assets/texture/stopButton.png", GL_NEAREST);

    this->playBtnIcon = this->playBtnIconTexture;

    GameEngine::FrameBufferSpecification viewportSpec;
    viewportSpec.width = this->viewportSize.x;
    viewportSpec.height = this->viewportSize.y;
    viewportSpec.attachments = {
        GameEngine::FrameBufferTextureFormat::RGBA8,
        GameEngine::FrameBufferTextureFormat::RED_INTEGER, //mouse picking
        GameEngine::FrameBufferTextureFormat::Depth
    };
    this->viewportFrameBuffer = new GameEngine::FrameBuffer(viewportSpec);
    GameEngine::cameraController->setViewTarget(&this->editorCamera, &this->editorCamera.transformComponent);

    GameEngine::FrameBufferSpecification cameraPreviewSpec;
    cameraPreviewSpec.width = 200;
    cameraPreviewSpec.height = 200;
    cameraPreviewSpec.attachments = {
        GameEngine::FrameBufferTextureFormat::RGBA8,
        GameEngine::FrameBufferTextureFormat::Depth
    };
    this->cameraViewFrameBuffer = new GameEngine::FrameBuffer(cameraPreviewSpec);

    this->imguiLayer.setup();

    GameEngine::EventDispatcher::addCallback("OpenProjectEvent", [this](GameEngine::Event* event) {
        GameEngineEditor::OpenProjectEvent* openProjectEvent = dynamic_cast<GameEngineEditor::OpenProjectEvent*>(event);
        if (openProjectEvent != nullptr)
            this->openProject(openProjectEvent->getProjectPath());
        return true;
    });

    GameEngine::EventDispatcher::addCallback("SaveProjectEvent", [this](GameEngine::Event* event) {
        if (event)
        {
            this->saveProject();
            return true;
        }
        return false;
    });

    GameEngine::EventDispatcher::addCallback("ImTreeNodeClickEvent", [this](GameEngine::Event* event) {
        GameEngineEditor::ImTreeNodeClickEvent* treeNodeClickEvent = dynamic_cast<GameEngineEditor::ImTreeNodeClickEvent*>(event);
        if (treeNodeClickEvent != nullptr)
        {
            this->selectedActor.setEntityID((entt::entity)treeNodeClickEvent->getSelectedEntityID());
        }
        return true;
    });
}

void GameEngineEditor::Editor::update(float deltaTime)
{
    if (this->sceneState == GameEngineEditor::SceneState::Play)
    {
        this->activeScene->unpdateRuntimeScene(deltaTime);
    }
}

void GameEngineEditor::Editor::render()
{
    bool snap = GameEngine::Input::isKeyPressed(GameEngine::Key_LCTRL);
    float snapValue = (this->gizmoOperation == ImGuizmo::ROTATE) ? 45.0f : 10.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(this->window);
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    this->imguiLayer.renderDockspace();

    if (this->selectedActor && this->selectedActor.hasComponent<GameEngine::CameraComponent>())
    {
        GameEngine::CameraComponent& cameraComponent = this->selectedActor.getComponent<GameEngine::CameraComponent>();
        GameEngine::TransformComponent& transformComponent = this->selectedActor.getComponent<GameEngine::TransformComponent>();
        this->imguiLayer.renderCameraPreview(reinterpret_cast<void*>(this->cameraViewFrameBuffer->getColorAttachmentRendererID()), cameraComponent.camera.getAspectRatio());
        ImVec2 currentViewportSize = this->imguiLayer.getCameraPreviewSize();
        //framebuffer sizeo = 0會出錯
        if ((currentViewportSize.x > 0.0f) && (currentViewportSize.y > 0.0f) &&
            ((this->cameraPreviewSize.x != currentViewportSize.x) || (this->cameraPreviewSize.y != currentViewportSize.y)))
        {
            this->cameraPreviewSize = currentViewportSize;
            this->cameraViewFrameBuffer->resize(this->cameraPreviewSize.x, this->cameraPreviewSize.y);
        }
        this->cameraViewFrameBuffer->bind();
        GameEngine::Renderer::begin(cameraComponent.camera, transformComponent.getTransform());
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            this->activeScene->render();
        GameEngine::Renderer::close();
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    //tab bar的hide button color
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0, 0, 0, 0});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0, 0, 0, 0});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0, 0, 0, 0});
    ImGui::Begin("viewport", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);
        ImVec2 viewportPos = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();

        //render toolbar
        static const float toolbarHeight = 32;
        static const float buttonSize = 32;
        static const ImGuiWindowFlags toolbarFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings;
        ImGui::SetNextWindowSize({windowSize.x, toolbarHeight});
        ImGui::SetNextWindowPos(viewportPos);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, GameEngineEditor::TitleBarColor);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {0, 0});
        ImGui::Begin("viweport-toolbar", NULL, toolbarFlags);
            //將工具item置中
            float toolbarWidth = ImGui::GetWindowSize().x;
            float centerPosForBtn = (toolbarWidth - buttonSize) / 2;
            ImGui::SetCursorPosX(centerPosForBtn);
            if (ImGui::ImageButton(reinterpret_cast<void*>(this->playBtnIcon->getTextureID()), {buttonSize, buttonSize}, {0, 1}, {1, 0}))
            {
                if (this->sceneState == GameEngineEditor::SceneState::Edit)
                    this->needToStartScene = true;
                else
                    this->needToStopScene = true;
            }
        ImGui::End();
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(1);

        this->isFocusOnViewport = ImGui::IsWindowFocused();
        ImVec2 currentViewportSize = ImGui::GetContentRegionAvail();
        //framebuffer sizeo = 0會出錯
        if ((currentViewportSize.x > 0.0f) && (currentViewportSize.y > 0.0f) &&
            ((this->viewportSize.x != currentViewportSize.x) || (this->viewportSize.y != currentViewportSize.y)))
        {
            this->viewportSize = currentViewportSize;
            this->editorCamera.resize(this->viewportSize.x, this->viewportSize.y);
            
            this->viewportFrameBuffer->resize(this->viewportSize.x, this->viewportSize.y);
        }

        //計算滑鼠在viewport的座標位置
        static int mx, my;
        GameEngine::Input::getMousePosition(&mx, &my);
        float menubarHeight = windowSize.y - this->viewportSize.y;
        this->viewportBound[0] = {viewportPos.x, viewportPos.y + menubarHeight};
        this->viewportBound[1] = {this->viewportBound[0].x + this->viewportSize.x, this->viewportBound[0].y + this->viewportSize.y};
        mx = mx - this->viewportBound[0].x;
        my = my - this->viewportBound[0].y;
        //翻轉y使(0, 0)在左下角，以符合OpenGL坐標系
        my = this->viewportSize.y - my;

        uint32_t textureID = this->viewportFrameBuffer->getColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void*>(textureID), currentViewportSize, ImVec2(0, 1), ImVec2(1, 0));
    
        if (ImGui::BeginDragDropTarget())
        {
            const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentBrowserItem");
            if (payload)
            {
                const wchar_t* itemPath = (const wchar_t*)payload->Data;
                glm::vec3 windowCoord = {mx, my, 0};
                //將screen coordinates 轉換成 world coordinates
                glm::vec3 worldCoord = glm::unProject(windowCoord, glm::mat4(1.0f), this->editorCamera.getProjectionMatrix(), (glm::vec4){0.0f, 0.0f, viewportSize.x, (float)viewportSize.y});
                GameEngineEditor::SDLFileParser::parseFile(itemPath, {worldCoord.x, worldCoord.y}, this->activeScene);
            }
            ImGui::EndDragDropTarget();
        }

        entt::entity selectedEntityID = (entt::entity)this->selectedActor.getID();
        if (selectedEntityID != entt::null)
        {
            ImGuizmo::SetOrthographic(true);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(this->viewportBound[0].x, this->viewportBound[0].y, this->viewportSize.x, this->viewportSize.y);
            const glm::mat4& cameraProjection = this->editorCamera.getProjection();
            glm::mat4 cameraView = glm::inverse(this->editorCamera.getTransform());
            GameEngine::TransformComponent& transformComponent = this->activeScene->queryActorComponent<GameEngine::TransformComponent>(selectedEntityID);
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
    ImGui::End();
    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(3);
    this->imguiLayer.renderAllPanel(this->fps);
    ImGui::Render();

    GameEngine::GEngine->textureManager->processCreateTextureTasks();

    //Render放在這邊才不會使viewport改變大小時出現閃爍
    this->viewportFrameBuffer->bind();
    GameEngine::Renderer::begin((*GameEngine::cameraController->getCamera()), GameEngine::cameraController->getTransform());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->activeScene->render();
        this->viewportFrameBuffer->clearAttachment(1, -1);
    GameEngine::Renderer::close();

    if (mx >= 0 && mx < this->viewportSize.x && my >= 0 && my < this->viewportSize.y)
    {
        //讀點到的pixel的entity id(預設-1)
        int pixelData = this->viewportFrameBuffer->readPixel(1, mx, my);
        if (GameEngine::Input::isMouseButtonPressed(GameEngine::Mouse_BUTTON_LEFT))
        {
            if (!ImGuizmo::IsOver() && this->isFocusOnViewport)
            {
                this->selectedActor.setEntityID((pixelData == -1) ? entt::null : (entt::entity)pixelData);
                this->imguiLayer.setSelectedEntityID(this->selectedActor.getID());
            }
        }
    }
    
    //要處理完mouse picking後才能unbind()
    this->viewportFrameBuffer->unbind();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GameEngineEditor::Editor::gameEventHandle()
{
    //清除SDL鍵盤事件
    // SDL_ResetKeyboard();
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
            case SDL_KEYDOWN:
            {
                if (this->event.key.repeat == 0)
                {
                    GameEngine::Script::KeyDownEvent keyDownEvent((GameEngine::KeyCode)(this->event.key.keysym.scancode));
                    GameEngine::Script::ScriptEventDispatcher::trigger<GameEngine::Script::KeyDownEvent>(&keyDownEvent);
                }
                break;
            }
            case SDL_KEYUP:
            {
                if (this->event.key.repeat == 0)
                {
                    GameEngine::Script::KeyUpEvent keyUpEvent((GameEngine::KeyCode)(this->event.key.keysym.scancode));
                    GameEngine::Script::ScriptEventDispatcher::trigger<GameEngine::Script::KeyUpEvent>(&keyUpEvent);
                }
                break;
            }
            default:
                break;
        }
    }

    if (GameEngine::Input::isKeyPressed(GameEngine::Key_E))
        this->gizmoOperation = ImGuizmo::SCALE;
    else if (GameEngine::Input::isKeyPressed(GameEngine::Key_R))
        this->gizmoOperation = ImGuizmo::ROTATE;
    else if (GameEngine::Input::isKeyPressed(GameEngine::Key_G))
        this->gizmoOperation = ImGuizmo::TRANSLATE;

    this->imguiLayer.eventHandle();
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

void GameEngineEditor::Editor::initNative()
{
#if USE_WINDOWS
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(this->window, &wmInfo);
    this->imguiLayer.setWindowID(wmInfo.info.win.window);
    // 設定DPI -> 要調字體大小
    SetProcessDPIAware();
#endif
}

void GameEngineEditor::Editor::openProject(const std::string& projectPath)
{
    this->projectParser.load(projectPath);
    GameEngine::GEngine->setProjectRootPath(this->projectParser.getProjectDirname());
    GameEngine::GEngine->setProjectName(this->projectParser.getProjectName());
    this->imguiLayer.setProjectRootPath(this->projectParser.getProjectDirname());

    std::filesystem::path mapPath(this->projectParser.getProjectDirname());
    mapPath /= "assets/scene/" + this->projectParser.getProjectName() + ".map";
    if (std::filesystem::exists(mapPath))
    {
        GameEngine::SceneSerializer sceneSerializer(&this->activeScene);
        if (sceneSerializer.deserialize(mapPath.string()))
        {
            this->imguiLayer.setScene(this->activeScene);
            this->selectedActor.bindScene(this->activeScene);
            GameEngine::ConsoleApi::log("Load scene success.\n");
        }
        else
        {
            GameEngine::ConsoleApi::log("Fail to load scene.\n");
        }
    }
}

void GameEngineEditor::Editor::saveProject()
{
    if (!this->projectParser.getProjectPath().empty())
    {
        GameEngine::SceneSerializer sceneSerializer(&this->activeScene);
        sceneSerializer.serialize(this->projectParser.getProjectDirname() + "/assets/scene/" + this->projectParser.getProjectName() + ".map");
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
        this->fps = 1.0 / ((time - this->lastFrameTime) / (float)SDL_GetPerformanceFrequency());
        this->gameEventHandle();

        if (this->needToStartScene)
            this->onSceneRuntimeStart();
        if (this->needToStopScene)
            this->onSceneRuntimeStop();

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

void GameEngineEditor::Editor::onSceneRuntimeStart()
{
    this->needToStartScene = false;
    this->playBtnIcon = this->stopBtnIconTexture;
    this->sceneState = GameEngineEditor::SceneState::Play;
    this->editorScene = GameEngine::Scene::copy(this->activeScene);
    this->activeScene->onRuntimeStart(this->projectParser.getProjectDirname());

    this->imguiLayer.setScene(this->activeScene);
}

void GameEngineEditor::Editor::onSceneRuntimeStop()
{
    this->needToStopScene = false;
    this->playBtnIcon = this->playBtnIconTexture;
    this->sceneState = GameEngineEditor::SceneState::Edit;
    this->activeScene = GameEngine::Scene::copy(this->editorScene);
    this->activeScene->onRunTimeStop();
    delete this->editorScene;
    this->editorScene = nullptr;

    GameEngine::cameraController->setViewTarget(&this->editorCamera, &this->editorCamera.transformComponent);

    this->imguiLayer.setScene(this->activeScene);
}
