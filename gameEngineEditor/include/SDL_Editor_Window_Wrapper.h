#ifndef SDL_EDITOR_WINDOW_WRAPPER_H
#define SDL_EDITOR_WINDOW_WRAPPER_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>

class SDL_Editor_Window_Wrapper: public QWidget
{
    Q_OBJECT
public:
    SDL_Editor_Window_Wrapper(QWidget* parent);
protected:
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
};

#endif