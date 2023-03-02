#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , projectParser(new ProjectParser())
    , flowLayout_fileSystemPanel(new FlowLayout())
    , fileSpriteSheet(new QPixmap("./assets/texture/filesystem.png"))
{
    ui->setupUi(this);
    
    this->ui->scrollAreaWidgetContents->setLayout(this->flowLayout_fileSystemPanel);
    
    QFile qssFile("./qss/gameEngineEditor_ui.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss = QString::fromUtf8(qssFile.readAll());
    this->setStyleSheet(qss);
    qssFile.close();

    connect(ui->actionopen, SIGNAL(triggered()), this, SLOT(openProject()));
    this->ui->wrapWidgetBottom->resize(this->ui->wrapWidgetBottom->width(), 120);
    this->ui->dockWidgetContentsBottom->resize(this->ui->dockWidgetContentsBottom->width(), 120);
    this->resizeDocks({this->ui->dockWidgetBottom}, {this->ui->dockWidgetContentsBottom->height()}, Qt::Vertical);

    this->ui->textBrowser->setTextColor(Qt::white);
    this->ui->textBrowser->append("Test");
    this->ui->textBrowser->append("Test");
    this->ui->textBrowser->append("Test");
    this->ui->textBrowser->append("Test");
    this->ui->textBrowser->append("Test");
    this->ui->textBrowser->append("Test");
    this->ui->textBrowser->append("Test");
    this->ui->textBrowser->append("Test");
    this->ui->textBrowser->append("Test");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->projectParser;
}

void MainWindow::clearFileSystemPanel()
{
    QLayoutItem* _item;
    QWidget* _widget;
    while (_item = this->flowLayout_fileSystemPanel->takeAt(0))
    {
        _widget = _item->widget();
        delete _widget;
        delete _item;
    }
}

void MainWindow::resetFileSystemPanel()
{
    this->clearFileSystemPanel();

    if (!std::filesystem::exists(this->currentPath))
        return;
    std::filesystem::directory_entry entry(this->currentPath);
    std::filesystem::directory_iterator fileList(this->currentPath);
    std::string filename;
    AssetFileWidget* assetFileWidget;
    for (auto& file: fileList)
    {
        filename = file.path().filename().u8string();
        if (std::filesystem::is_directory(file.path()))
            assetFileWidget = new AssetFileWidget(filename, this->fileSpriteSheet, FileType::Fold);
        else
            assetFileWidget = new AssetFileWidget(filename, this->fileSpriteSheet, FileType::File);
        this->flowLayout_fileSystemPanel->addWidget(assetFileWidget);
        connect(assetFileWidget, &AssetFileWidget::click, this, &MainWindow::filesystemPanel_click);
    }
}

void MainWindow::openProject()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open project"), QDir::homePath(), tr("*.gproject"));
    this->projectParser->load(path.toStdString().c_str());
    this->currentPath = this->projectParser->getProjectDirname();
    this->resetFileSystemPanel();
}

void MainWindow::filesystemPanel_click()
{
    AssetFileWidget* assetFileWidgget = qobject_cast<AssetFileWidget*>(QObject::sender());
    this->currentPath /= assetFileWidgget->getAssetName();
    this->resetFileSystemPanel();
    return;
}