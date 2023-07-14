#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QProcess>
#include <QMouseEvent>
#include <QMessageBox>
#include <filesystem>
#include <QColorDialog>
#include <QCloseEvent>
#include <QTimer>
#include "flowlayout.h"
#include "EditorOpenGLWidget.h"
#include "ProjectParser.h"
#include "AssetFileWidget.h"
#include "EditorScene.h"
#include "OutlineTreeWidgetItem.h"
#include <vector>
#include "entt.hpp"
#include "Component/Component.h"
#include "Scene/SceneSerializer.h"
#include "runtime/compile/CompileProcess.h"
#include "SDL_Editor_Window.h"
#include "SDL_Editor_Window_Wrapper.h"
#include "glm/glm.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void embedSDL(WId winId, SDL_Editor_Window* newSDL_Window);
    void onFocusChanged(bool& isFocusOnSDL);
private:
    Ui::MainWindow *ui;

    ProjectParser* projectParser;
    FlowLayout* flowLayout_fileSystemPanel;
    QPixmap* fileSpriteSheet;
    std::filesystem::path currentPath;
    QTreeWidgetItem* actorLevel;
    CompileProcess compileProcess;
    SDL_Editor_Window* SDL_editor_window;
    SDL_Editor_Window_Wrapper* SDLWidget;
    QTimer timer;

    /*重新刷新File system panel*/
    void resetFileSystemPanel();
    void clearOutline();
    void updateColorViewer();
protected:
    void closeEvent (QCloseEvent* event);
private slots:
    void openProject();
    void saveScene();
    void filesystemPanel_click();
    /*用於clear all item in flowLayout*/
    void clearFileSystemPanel();
    void parseOutput();
    void resetGameObjectOutline();
    void getTreeWigetItemInfo(QTreeWidgetItem* item, int column);
    void openColorDialog();
    void compileProject();
    void runProject();
};

#endif // MAINWINDOW_H