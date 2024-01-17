#ifndef SDL_EDITOR_WINDOW_WRAPPER_H
#define SDL_EDITOR_WINDOW_WRAPPER_H

#include <QWidget>
#include <QWindow>
#include <QMouseEvent>
#include <QKeyEvent>

class SDL_Editor_Window_Wrapper_Window: public QWindow
{
    Q_OBJECT
public:
    SDL_Editor_Window_Wrapper_Window(QWindow* parent);
protected:
    bool event(QEvent* e);
};

class SDL_Editor_Window_Wrapper: public QWidget
{
    Q_OBJECT
public:
    SDL_Editor_Window_Wrapper(QWidget* parent);
};

#endif