#ifndef EDITOR_OPENGL_WIDGET_H
#define EDITOR_OPENGL_WIDGET_H

#include "GL/glew.h"
#include <QOpenGLWidget>
#include <QKeyEvent>

#include "GameEngineAPI/GameEngineAPI.h"
#include "Renderer.h"
#include "EditorScene.h"

class EditorOpenGLWidget: public QOpenGLWidget
{
public:
    EditorOpenGLWidget(QWidget* parent = nullptr);
private:
    void sceneBegin();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent* event);
};

#endif