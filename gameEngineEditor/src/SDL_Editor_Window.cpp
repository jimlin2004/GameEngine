#include "SDL_Editor_Window.h"
#include "Event/Input.h"
#include <winuser.h>

SDL_Editor_Window::SDL_Editor_Window(const char* title, int width, int height)
    : GameBase(title, width, height)
    , isFocusOnSDLPtr(nullptr)
    , isCompleteFocusChange(true)
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
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

void SDL_Editor_Window::update(float deltaTime)
{
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_E))
        GameEngine::ConsoleApi::log("HI\n");
}

void SDL_Editor_Window::render()
{
    static int n = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(this->window);
    ImGui::NewFrame();

    ImGui::Begin("Hello Imgui");
        ImGui::Text("HI");
        ImGui::InputInt("Test", &n);
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    static float r = 0.0f;
    
    r += 0.001;
    if (r > 1.0f)
        r = 0.0f;
    GameEngine::Renderer::begin();
        GameEngine::Renderer::drawQuad({100.0f, 30.0f, 1.0f}, {50.0f, 50.0f}, {r, 0.0f, 0.0f, 1.0f});
        GameEngine::globalScene->render();
    GameEngine::Renderer::close();
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
    if (GameEngine::Input::isKeyPressed(GameEngine::Key_E))
        GameEngine::ConsoleApi::log("HI\n");
    if (GameEngine::Input::isMouseButtonPressed(GameEngine::Mouse_BUTTON_LEFT))
    {
        if (*(this->isFocusOnSDLPtr) == false)
        {
            SDL_SysWMinfo wmInfo;
            SDL_VERSION(&wmInfo.version);
            SDL_GetWindowWMInfo(this->window, &wmInfo);
            SetForegroundWindow(wmInfo.info.win.window);
            // auto temp = SDL_GetKeyboardFocus();
            // auto tep = SDL_GetMouseFocus();
            SetFocus(wmInfo.info.win.window);
            *(this->isFocusOnSDLPtr) = true;
        }
        
        // printf("temp\n");
    }
}

void SDL_Editor_Window::bindisFocusOnSDL(bool *ptr)
{
    this->isFocusOnSDLPtr = ptr;
}
