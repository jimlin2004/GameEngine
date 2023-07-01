#include "mainwindow.h"
#include "./ui_mainwindow.h"

static QTextBrowser* _textBrowserPtr;

static void textBrowserSetColor(const Qt::GlobalColor color)
{
    _textBrowserPtr->setTextColor(color);
}

static void textBrowserInsert(const QString& text, const Qt::GlobalColor color = Qt::white)
{
    _textBrowserPtr->moveCursor(QTextCursor::End);
    /*
        改變顏色必須在 insert text之前，否則可能因為Qt在文字前的顏色
        標記被moveCursor因此失效(未證實，但的確發生)
    */
    textBrowserSetColor(color);
    _textBrowserPtr->insertPlainText(text);
    _textBrowserPtr->moveCursor(QTextCursor::End);
}

static void logMsgToTextBrowser(QtMsgType type, Qt::GlobalColor color, const QMessageLogContext &context, const QString& msg)
{
    switch (type)
    {
    case QtDebugMsg:
        textBrowserInsert("[Debug] " + msg, color);
        break;
    case QtInfoMsg:
        textBrowserInsert("[Info] " + msg, color);
        break;
    case QtWarningMsg:
        textBrowserInsert("[Warning] " + msg, color);
        break;
    case QtCriticalMsg:
        textBrowserInsert("[Error] " + msg, color);
        break;
    case QtFatalMsg:
        textBrowserInsert("[Fatal error] " + msg, color);
        break;
    default:
        qFatal("Unknow message type\n");
        break;
    }
}

static void parseEditorMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    switch (type)
    {
    case QtDebugMsg:
        logMsgToTextBrowser(type, Qt::green, context, msg);
        break;
    case QtInfoMsg:
        logMsgToTextBrowser(type, Qt::white, context, msg);
        break;
    case QtWarningMsg:
        logMsgToTextBrowser(type, Qt::yellow, context, msg);
        break;
    case QtCriticalMsg:
        logMsgToTextBrowser(type, Qt::red, context, msg);
        break;
    case QtFatalMsg:
        logMsgToTextBrowser(type, Qt::red, context, msg);
        break;
    default:
        qFatal("Unknow message type\n");
        break;
    }
}

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

    this->ui->dockWidgetContentsRight->resize(100, this->ui->dockWidgetRight->height());
    this->resizeDocks({this->ui->dockWidgetRight}, {this->ui->dockWidgetRight->width()}, Qt::Horizontal);

    connect(this->ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(parseOutput()));
    
    _textBrowserPtr = this->ui->textBrowser;
    qInstallMessageHandler(parseEditorMsg);

    // Game Object outline
    this->ui->treeWidget->headerItem()->setText(0, "Collection");
    actorLevel = new QTreeWidgetItem(this->ui->treeWidget);
    actorLevel->setText(0, "Actor");

    connect(this->ui->openglWidget, &EditorOpenGLWidget::resetGameObjectOutline, this, &MainWindow::resetGameObjectOutline);
    connect(this->ui->treeWidget, &QTreeWidget::itemClicked, this, &MainWindow::getTreeWigetItemInfo);
    
    this->ui->scrollAreaWidgetContents_detail->layout()->setAlignment(Qt::AlignTop);
    // this->ui->dockWidgetContentsLeft->resize(100, this->ui->dockWidgetLeft->height());
    // this->resizeDocks({this->ui->dockWidgetLeft}, {this->ui->dockWidgetLeft->width()}, Qt::Horizontal);
    this->resizeDocks({this->ui->dockWidgetLeft}, {this->ui->scrollAreaWidgetContents_detail->width()}, Qt::Horizontal);
    
    this->ui->widget_colorViewer->setStyleSheet("background-color: #000000;");
    connect(this->ui->pushButton_colorPicker, &QPushButton::clicked, this, &MainWindow::openColorDialog);
    connect(this->ui->lineEditFloat_R_color, &LineEditFloat::editingFinished, this, &MainWindow::updateColorViewer);
    connect(this->ui->lineEditFloat_G_color, &LineEditFloat::editingFinished, this, &MainWindow::updateColorViewer);
    connect(this->ui->lineEditFloat_B_color, &LineEditFloat::editingFinished, this, &MainWindow::updateColorViewer);
    this->ui->pushButton_colorPicker->setEnabled(false); //為選取game object前不能點選
    // QTimer* timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this->ui->openglWidget, &EditorOpenGLWidget::updateGL);
    // timer->start(41); //24fps
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

void MainWindow::clearOutline()
{

}

void MainWindow::getTreeWigetItemInfo(QTreeWidgetItem* item, int column)
{
    OutlineTreeWidgetItem* outlineItem = dynamic_cast<OutlineTreeWidgetItem*>(item);
    if (outlineItem != nullptr)
        outlineItem->click();
    GameEngine::TransformComponent& transformComponent = GameEngine::globalScene->queryActorComponent<GameEngine::TransformComponent>(outlineItem->getEntityID());
    GameEngine::MeshComponent& meshComponent = GameEngine::globalScene->queryActorComponent<GameEngine::MeshComponent>(outlineItem->getEntityID());
    this->ui->lineEditFloat_x_position->bind(&transformComponent.translation.x);
    this->ui->lineEditFloat_y_position->bind(&transformComponent.translation.y);
    this->ui->lineEditFloat_z_position->bind(&transformComponent.translation.z);
    this->ui->lineEditFloat_x_scale->bind(&transformComponent.scale.x);
    this->ui->lineEditFloat_y_scale->bind(&transformComponent.scale.y);
    this->ui->lineEditFloat_z_scale->bind(&transformComponent.scale.z);
    this->ui->lineEditFloat_x_rotation->bind(&transformComponent.rotation.x);
    this->ui->lineEditFloat_y_rotation->bind(&transformComponent.rotation.y);
    this->ui->lineEditFloat_z_rotation->bind(&transformComponent.rotation.z);
    this->ui->lineEditFloat_R_color->bind(&meshComponent.color.r);
    this->ui->lineEditFloat_G_color->bind(&meshComponent.color.g);
    this->ui->lineEditFloat_B_color->bind(&meshComponent.color.b);
    this->ui->pushButton_colorPicker->setEnabled(true);
    this->updateColorViewer();
}

void MainWindow::openColorDialog()
{
    QColor color = QColorDialog::getColor();
    this->ui->lineEditFloat_R_color->setValue(color.redF());
    this->ui->lineEditFloat_G_color->setValue(color.greenF());
    this->ui->lineEditFloat_B_color->setValue(color.blueF());
    this->updateColorViewer();
}

void MainWindow::updateColorViewer()
{
    int R = (int)(this->ui->lineEditFloat_R_color->getValue() * 255);
    int G = (int)(this->ui->lineEditFloat_G_color->getValue() * 255);
    int B = (int)(this->ui->lineEditFloat_B_color->getValue() * 255);
    QColor color(R, G, B);
    this->ui->widget_colorViewer->setStyleSheet("background-color: " + color.name() + ";");
    this->ui->openglWidget->update();
}

void MainWindow::resetGameObjectOutline()
{
    this->clearOutline();
    std::vector<entt::entity> entities = EditorScene::getAllActors();
    for (entt::entity entity: entities)
    {
        OutlineTreeWidgetItem* item = new OutlineTreeWidgetItem();
        GameEngine::TagComponent& tagComponent = GameEngine::globalScene->queryActorComponent<GameEngine::TagComponent>(entity);
        item->setText(0, QString::fromStdString(tagComponent.tagName));
        item->setEntityID(entity);
        this->actorLevel->addChild(item);
    }
}

void MainWindow::openProject()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open project"), QDir::homePath(), tr("*.gproject"));
    this->projectParser->load(path.toStdString().c_str());
    this->currentPath = this->projectParser->getProjectDirname();
    this->currentPath /= "content";
    this->resetFileSystemPanel();
    qDebug("Load project success.\n");
    qDebug("Current project: %s.\n", this->projectParser->getProjectName().c_str());
}

void MainWindow::filesystemPanel_click()
{
    AssetFileWidget* assetFileWidgget = qobject_cast<AssetFileWidget*>(QObject::sender());
    this->currentPath /= assetFileWidgget->getAssetName();
    this->resetFileSystemPanel();
    return;
}

void MainWindow::parseOutput()
{
    textBrowserInsert(this->ui->lineEdit->text() + "\n");
    this->ui->lineEdit->clear();
}