#ifndef EDITOR_OPENGL_WIDGET_H
#define EDITOR_OPENGL_WIDGET_H

#include "GL/glew.h"
#include <QOpenGLWidget>

#include "Renderer.h"

class EditorOpenGLWidget: public QOpenGLWidget
{
public:
    EditorOpenGLWidget(QWidget* parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif