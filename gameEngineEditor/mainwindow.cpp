#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), projectParser(new ProjectParser())
{
    ui->setupUi(this);
    
    this->resetFileSystemPanel();

    QFile qssFile("./qss/gameEngineEditor_ui.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss = QString::fromUtf8(qssFile.readAll());
    this->setStyleSheet(qss);
    qssFile.close();

    connect(ui->actionopen, SIGNAL(triggered()), this, SLOT(openProject()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->projectParser;
}

void MainWindow::resetFileSystemPanel()
{
    this->ui->gridLayout_fileSystemPanel->addWidget(new AssetFileWidget("Test"), 0, 0);
    this->ui->gridLayout_fileSystemPanel->addWidget(new AssetFileWidget("Test"), 0, 1);
    this->ui->gridLayout_fileSystemPanel->addWidget(new AssetFileWidget("Test"), 0, 2);
    this->ui->gridLayout_fileSystemPanel->addWidget(new AssetFileWidget("Test"), 0, 3);
}

void MainWindow::openProject()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open project"), QDir::homePath(), tr("*.gproject"));
    this->projectParser->load(path.toStdString().c_str());
}