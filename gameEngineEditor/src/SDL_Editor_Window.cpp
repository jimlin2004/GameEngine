#include "SDL_Editor_Window.h"
#include "Event/Input.h"

SDL_Editor_Window::SDL_Editor_Window(const char* title, int width, int height)
    : GameBase(title, width, height)
{
}

SDL_Editor_Window::~SDL_Editor_Window()
{
}

void SDL_Editor_Window::init()
{
    GameEngine::Renderer::init();
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
}
