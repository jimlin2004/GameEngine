#include "mainwindow.h"

#include <QFontDatabase>
#include <QDebug>
#include <QApplication>
#include "SDL_Editor_Window.h"
#include <thread>

#undef main //SDL_main

bool isRunSDL = false;
WId SDL_Editor_Window_ID;
SDL_Editor_Window* SDL_editor_window;

void runSDL()
{
    SDL_editor_window = new SDL_Editor_Window("SDLwindow", 640, 480);
    bool success = SDL_editor_window->initSDL() && SDL_editor_window->initGL() && SDL_editor_window->initImGui();
    if (!success)
    {
        GameEngine::ConsoleApi::log("Can not open SDL\n");
        return;
    }
    SDL_editor_window->init();
    SDL_editor_window->logBuildInfo();
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(SDL_editor_window->window, &wmInfo);
    SDL_Editor_Window_ID = (WId)wmInfo.info.win.window;
    isRunSDL = true;
    SDL_editor_window->startGame();
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 0);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    QFontDatabase::addApplicationFont("assets/font/CascadiaMono.ttf");
    std::thread SDL_thread(runSDL);
    SDL_thread.detach();
    while (!isRunSDL)
        ;
    MainWindow w;
    
    w.embedSDL(SDL_Editor_Window_ID, SDL_editor_window);
    w.show();

    qDebug("Create Editor success\n");
    qDebug("Running environment version: %s\n", "1.0 alpha");

    return a.exec();
}