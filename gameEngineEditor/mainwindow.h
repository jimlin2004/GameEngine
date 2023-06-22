#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QProcess>
#include <QTimer>
#include <filesystem>
#include "flowlayout.h"
#include "EditorOpenGLWidget.h"
#include "ProjectParser.h"
#include "AssetFileWidget.h"
#include "EditorScene.h"
#include "OutlineTreeWidgetItem.h"
#include <vector>
#include "entt.hpp"
#include "Component/Component.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    ProjectParser* projectParser;
    FlowLayout* flowLayout_fileSystemPanel;
    QPixmap* fileSpriteSheet;
    std::filesystem::path currentPath;
    QTreeWidgetItem* actorLevel;

    /*重新刷新File system panel*/
    void resetFileSystemPanel();
    void clearOutline();
private slots:
    void openProject();
    void filesystemPanel_click();
    /*用於clear all item in flowLayout*/
    void clearFileSystemPanel();
    void parseOutput();
    void resetGameObjectOutline();
    void getTreeWigetItemInfo(QTreeWidgetItem* item, int column);
};

#endif // MAINWINDOW_H