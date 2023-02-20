#include "EditorOpenGLWidget.h"

EditorOpenGLWidget::EditorOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{

}

void EditorOpenGLWidget::initializeGL()
{
    if (glewInit() != 0)
    {
        qFatal("glewInit failed");
        return;
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    GameEngine::Renderer::init();

}

void EditorOpenGLWidget::resizeGL(int w, int h)
{

}

void EditorOpenGLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GameEngine::Renderer::begin();
        GameEngine::Renderer::drawQuad({-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f});
    GameEngine::Renderer::close();
}