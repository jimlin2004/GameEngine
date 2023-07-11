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
