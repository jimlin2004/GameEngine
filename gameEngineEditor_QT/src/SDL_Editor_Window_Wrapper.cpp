#include "SDL_Editor_Window_Wrapper.h"

SDL_Editor_Window_Wrapper::SDL_Editor_Window_Wrapper(QWidget *parent)
    : QWidget(parent)
{
    this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

SDL_Editor_Window_Wrapper_Window::SDL_Editor_Window_Wrapper_Window(QWindow *parent)
    : QWindow(parent)
{
}

bool SDL_Editor_Window_Wrapper_Window::event(QEvent *e)
{
    return QWindow::event(e);
}
