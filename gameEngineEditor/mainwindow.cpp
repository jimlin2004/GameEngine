#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , projectParser(new ProjectParser())
    , flowLayout_fileSystemPanel(new FlowLayout())
{
    ui->setupUi(this);
    
    this->ui->scrollAreaWidgetContents->setLayout(this->flowLayout_fileSystemPanel);

    // this->resetFileSystemPanel();

    // this->ui->wrapWidgetBottom->resize(this->ui->wrapWidgetBottom->size().width(), 60);
    
    QFile qssFile("./qss/gameEngineEditor_ui.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss = QString::fromUtf8(qssFile.readAll());
    this->setStyleSheet(qss);
    qssFile.close();

    connect(ui->actionopen, SIGNAL(triggered()), this, SLOT(openProject()));
    this->ui->wrapWidgetBottom->resize(this->ui->wrapWidgetBottom->width(), 120);
    this->ui->dockWidgetContentsBottom->resize(this->ui->dockWidgetContentsBottom->width(), 120);
    this->resizeDocks({this->ui->dockWidgetBottom}, {this->ui->dockWidgetContentsBottom->height()}, Qt::Vertical);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->projectParser;
}

void MainWindow::resetFileSystemPanel()
{
    // this->flowLayout_fileSystemPanel->addWidget(new AssetFileWidget("Test"));
    // this->flowLayout_fileSystemPanel->addWidget(new AssetFileWidget("Test"));
    // this->flowLayout_fileSystemPanel->addWidget(new AssetFileWidget("Test"));
    // this->flowLayout_fileSystemPanel->addWidget(new AssetFileWidget("Test"));
    std::filesystem::path entryPath(this->projectParser->getProjectDirname());
    if (!std::filesystem::exists(entryPath))
        return;
    std::filesystem::directory_entry entry(entryPath);
    std::filesystem::directory_iterator fileList(entryPath);
    std::string filename;
    for (auto& file: fileList)
    {
        filename = file.path().filename().u8string();
        this->flowLayout_fileSystemPanel->addWidget(new AssetFileWidget(filename));
    }
}

void MainWindow::openProject()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open project"), QDir::homePath(), tr("*.gproject"));
    this->projectParser->load(path.toStdString().c_str());
    this->resetFileSystemPanel();
}