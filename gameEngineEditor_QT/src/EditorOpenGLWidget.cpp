// #include "EditorOpenGLWidget.h"

// EditorOpenGLWidget::EditorOpenGLWidget(QWidget* parent)
//     : QOpenGLWidget(parent)
// {
//     setFocusPolicy(Qt::ClickFocus);
//     setFocus();
// }

// void EditorOpenGLWidget::sceneBegin()
// {
//     EditorScene::addActor<GameEngine::Actor>({100.0f, 100.0f, 1.0f}, {50.0f, 50.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, "TestActor");
//     EditorScene::addActor<GameEngine::Actor>({250.0f, 100.0f, 1.0f}, {50.0f, 50.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, "TestActor");
//     this->resetGameObjectOutline();
// }

// void EditorOpenGLWidget::initializeGL()
// {
//     if (glewInit() != 0)
//     {
//         qFatal("glewInit failed");
//         return;
//     }

//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glEnable(GL_DEPTH_TEST);

//     GameEngine::Renderer::init();
//     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

//     GameEngine::cameraController->setSpeed(5.0f);
//     this->sceneBegin();
// }

// void EditorOpenGLWidget::resizeGL(int w, int h)
// {
//     GameEngine::cameraController->setProjection(0, w, 0, h);
// }

// void EditorOpenGLWidget::paintGL()
// {
//     static float r = 0.0f;
//     r += 0.05f;
//     if (r >= 1.0f)
//         r = 0.0f;
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     GameEngine::Renderer::begin();
//         GameEngine::globalScene->render();
//         GameEngine::Renderer::drawQuad({300.0f, 300.0f, 1.0f}, {50.0f, 50.0f}, {r, 0.0f, 0.0f, 1.0f});
//     GameEngine::Renderer::close();
// }

// void EditorOpenGLWidget::keyPressEvent(QKeyEvent* event)
// {
//     //<Note> camera 移動方向是反的
//     switch (event->key())
//     {
//     case Qt::Key_W:
//     case Qt::Key_Up:
//         GameEngine::cameraController->moveCamera({0.0f, 1.0f, 0.0f});
//         this->update();
//         break;
//     case Qt::Key_D:
//     case Qt::Key_Right:
//         GameEngine::cameraController->moveCamera({1.0f, 0.0f, 0.0f});
//         this->update();
//         break;
//     case Qt::Key_S:
//     case Qt::Key_Down:
//         GameEngine::cameraController->moveCamera({0.0f, -1.0f, 0.0f});
//         this->update();
//         break;
//     case Qt::Key_A:
//     case Qt::Key_Left:
//     GameEngine::cameraController->moveCamera({-1.0f, 0.0f, 0.0f});
//         this->update();
//         break;
//     default:
//         break;
//     }
// }

// void EditorOpenGLWidget::mousePressEvent(QMouseEvent *event)
// {
//     qDebug("Click x: %f, y: %f\n", event->position().x(), event->position().y());
// }

// void EditorOpenGLWidget::clickGameObject(int x, int y)
// {

// }