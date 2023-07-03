#ifndef EDITOR_OPENGL_WIDGET_H
#define EDITOR_OPENGL_WIDGET_H

#include "GL/glew.h"
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>

#include "GameEngineAPI/GameEngineAPI.h"
#include "Renderer.h"
#include "EditorScene.h"
#include "Scene/SceneSerializer.h"

class EditorOpenGLWidget: public QOpenGLWidget
{
    Q_OBJECT
public:
    EditorOpenGLWidget(QWidget* parent = nullptr);
private:
    void sceneBegin();
    void clickGameObject(int x, int y);
signals:
    void resetGameObjectOutline();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
};

#endif