#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>
#include <QMouseEvent>
#include <QMessageBox>
#include <QColorDialog>
#include <QCloseEvent>
#include <QTimer>
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
#include "MainWindowExportData.h"

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
    inline GameEngineEditor::ExportData* getExportDataPtr() const
    {
        return &(this->exportData);
    }
private:
    Ui::MainWindow *ui;

    ProjectParser* projectParser;
    OutlineTreeWidgetItem* actorLevel;
    CompileProcess compileProcess;
    SDL_Editor_Window* SDL_editor_window;
    SDL_Editor_Window_Wrapper* SDLWidget;
    QTimer timer;
    static GameEngineEditor::ExportData exportData;

    void clearOutline();
    void updateColorViewer();
    void addGameObjectToOutline(entt::entity entityID);
    void resetTextureComboBox();
protected:
    void closeEvent (QCloseEvent* event);
private slots:
    void openProject();
    void saveScene();
    void parseOutput();
    void resetGameObjectOutline();
    void getTreeWigetItemInfo(QTreeWidgetItem* item, int column);
    void openColorDialog();
    void compileProject();
    void runProject();
    void updateTextureViewer();
    void updateWidgets();
};

#endif // MAINWINDOW_H