#include "SDL_Editor_Window.h"

#include "mainwindow.h"
#include <QFontDatabase>
#include <QDebug>
#include <QApplication>
// #undef QT_NEEDS_QMAIN

#include <thread>
#include <mutex>
#include <condition_variable>

bool isFocusOnSDL = false;
WId SDL_Editor_Window_ID = 0;
SDL_Editor_Window* SDL_editor_window = nullptr;

std::mutex m;
std::condition_variable conditionVar;

void runSDL()
{
    SDL_editor_window = new SDL_Editor_Window("SDLwindow", 640, 480);
    SDL_editor_window->bindIsFocusOnSDL(&isFocusOnSDL);
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
    
    conditionVar.notify_one(); //讓main thread繼續運行

    SDL_editor_window->startGame();
}

#ifdef QT_NEEDS_QMAIN
    #undef main
    #define main SDL_main
#endif

int main(int argc, char* argv[])
{
    std::unique_lock<std::mutex> lock(m);

    QApplication a(argc, argv);
    
    QFontDatabase::addApplicationFont("assets/font/CascadiaMono.ttf");
    std::thread SDL_thread(runSDL);
    SDL_thread.detach();   
    
    MainWindow w; 
    QObject::connect(&a, &QApplication::focusChanged, [&](){
        QWidget* widget = a.focusWidget();
        if(widget == nullptr) //Focus out
            return;
        w.onFocusChanged(isFocusOnSDL);
    });
    
    conditionVar.wait(lock); // 等待SDL thread

    w.embedSDL(SDL_Editor_Window_ID, SDL_editor_window);
    w.show();
    qDebug("Create Editor success\n");
    qDebug("Running environment version: %s\n", "1.0 alpha");

    return a.exec();
}