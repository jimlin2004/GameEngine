#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QMessageBox>
#include <QColorDialog>
#include <QCloseEvent>
#include <QTimer>
#include <QMenuBar>
#include <QToolBar>
#include <QSizePolicy>
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
#include "Core/Assert.h"

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
    qreal border;

    //actions
    QAction* actionRun;
    //
    static GameEngineEditor::ExportData exportData;

    void initTitlebar();
    void initToolbar();
    void clearOutline();
    void updateColorViewer();
    void addGameObjectToOutline(entt::entity entityID);
    void resetTextureComboBox();

    void ToMaximize();
    void ToNormal();

    template<class Component>
    void pushComponentProperty(const entt::entity& entityID = entt::null)
    {
        GAME_ENGINE_ASSERT(false, "Unknow Component type");
    }
    
    void hideAllDetail();
    void updateDetail();

protected:
    bool event(QEvent* event) override;
    void closeEvent (QCloseEvent* event);
#ifdef Q_OS_WIN
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
#endif
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
    void updateOutline();

    void onCloseClick();
    void onExpandClick();
    void onMinimizeClick();
    void onHitBorder(QPoint pos);
    
    void onTransformUpdate();
};

#endif // MAINWINDOW_H