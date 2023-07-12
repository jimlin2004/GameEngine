#include "SDL_Editor_Window_Wrapper.h"

SDL_Editor_Window_Wrapper::SDL_Editor_Window_Wrapper(QWidget *parent)
    : QWidget(parent)
{
    this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

void SDL_Editor_Window_Wrapper::mousePressEvent(QMouseEvent *event)
{
    qDebug("Click x: %f, y: %f\n", event->position().x(), event->position().y());
}

void SDL_Editor_Window_Wrapper::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "event->key(): " << event->key();

    QWidget::keyPressEvent(event);
}

bool SDL_Editor_Window_Wrapper::event(QEvent *e)
{   
    if (e->type() == QEvent::KeyPress)
        return true;
    return QWidget::event(e);
}

SDL_Editor_Window_Wrapper_Window::SDL_Editor_Window_Wrapper_Window(QWindow *parent)
    : QWindow(parent)
{
}

bool SDL_Editor_Window_Wrapper_Window::event(QEvent *e)
{
    return QWindow::event(e);
}
