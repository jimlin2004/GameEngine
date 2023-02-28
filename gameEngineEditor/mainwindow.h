#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <filesystem>
#include "flowlayout.h"
#include "EditorOpenGLWidget.h"
#include "ProjectParser.h"
#include "AssetFileWidget.h"

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

    void resetFileSystemPanel();

private slots:
    void openProject();
};

#endif // MAINWINDOW_H