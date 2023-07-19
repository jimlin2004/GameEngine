#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWindow>
#include "Core/Platform.h"
#if USE_WINDOWS
    #include <winuser.h>
    #include <windows.h>
#endif

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

GameEngineEditor::ExportData MainWindow::exportData;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , projectParser(new ProjectParser())
    , compileProcess(_textBrowserPtr)
    , SDL_editor_window(nullptr)
    , SDLWidget(nullptr)
{
    ui->setupUi(this);
    
    QFile qssFile("./qss/gameEngineEditor_ui.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss = QString::fromUtf8(qssFile.readAll());
    this->setStyleSheet(qss);
    qssFile.close();

    connect(this->ui->actionopen, &QAction::triggered, this, &MainWindow::openProject);
    connect(this->ui->actionsave, &QAction::triggered, this, &MainWindow::saveScene);
    this->ui->wrapWidgetBottom->resize(this->ui->wrapWidgetBottom->width(), 120);
    this->ui->dockWidgetContentsBottom->resize(this->ui->dockWidgetContentsBottom->width(), 120);
    this->resizeDocks({this->ui->dockWidgetBottom}, {this->ui->dockWidgetContentsBottom->height()}, Qt::Vertical);

    this->ui->dockWidgetContentsRight->resize(100, this->ui->dockWidgetRight->height());
    this->resizeDocks({this->ui->dockWidgetRight}, {this->ui->dockWidgetRight->width()}, Qt::Horizontal);

    connect(this->ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::parseOutput);
    
    _textBrowserPtr = this->ui->textBrowser;
    qInstallMessageHandler(parseEditorMsg);

    // Game Object outline
    this->ui->treeWidget->headerItem()->setText(0, "Collection");
    actorLevel = new OutlineTreeWidgetItem(this->ui->treeWidget);
    actorLevel->setText(0, "Actor");

    // connect(this->ui->openglWidget, &EditorOpenGLWidget::resetGameObjectOutline, this, &MainWindow::resetGameObjectOutline);
    connect(this->ui->treeWidget, &QTreeWidget::itemClicked, this, &MainWindow::getTreeWigetItemInfo);
    
    this->ui->scrollAreaWidgetContents_detail->layout()->setAlignment(Qt::AlignTop);
    // this->ui->dockWidgetContentsLeft->resize(100, this->ui->dockWidgetLeft->height());
    // this->resizeDocks({this->ui->dockWidgetLeft}, {this->ui->dockWidgetLeft->width()}, Qt::Horizontal);
    this->resizeDocks({this->ui->dockWidgetLeft}, {this->ui->scrollAreaWidgetContents_detail->width() + 20}, Qt::Horizontal);
    
    this->ui->widget_colorViewer->setStyleSheet("background-color: #000000;");
    connect(this->ui->pushButton_colorPicker, &QPushButton::clicked, this, &MainWindow::openColorDialog);
    connect(this->ui->lineEditFloat_R_color, &LineEditFloat::editingFinished, this, &MainWindow::updateColorViewer);
    connect(this->ui->lineEditFloat_G_color, &LineEditFloat::editingFinished, this, &MainWindow::updateColorViewer);
    connect(this->ui->lineEditFloat_B_color, &LineEditFloat::editingFinished, this, &MainWindow::updateColorViewer);
    this->ui->pushButton_colorPicker->setEnabled(false); //為選取game object前不能點選
    
    connect(this->ui->actioncompile, &QAction::triggered, this, &MainWindow::compileProject);
    connect(this->ui->actionrun, &QAction::triggered, this, &MainWindow::runProject);

    //bind tiemr to transform
    connect(&(this->timer), &QTimer::timeout, this, &MainWindow::updateWidgets);
    this->timer.start(41);

    //export data
    this->exportData.outlineTreeWidget = this->ui->treeWidget;
    this->exportData.actorCollection = this->actorLevel;

    this->ui->label_textureViewer->setStyleSheet("background: #000000;");
    connect(this->ui->comboBox_texture, &QComboBox::currentIndexChanged, this, &MainWindow::updateTextureViewer);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->projectParser;
}

void MainWindow::updateWidgets()
{
    if (!this->ui->lineEditFloat_x_position->isEditing())
        this->ui->lineEditFloat_x_position->refresh();
    if (!this->ui->lineEditFloat_y_position->isEditing())
        this->ui->lineEditFloat_y_position->refresh();
    if (!this->ui->lineEditFloat_z_position->isEditing())
        this->ui->lineEditFloat_z_position->refresh();
    if (!this->ui->lineEditFloat_x_scale->isEditing())
        this->ui->lineEditFloat_x_scale->refresh();
    if (!this->ui->lineEditFloat_y_scale->isEditing())
        this->ui->lineEditFloat_y_scale->refresh();
    if (!this->ui->lineEditFloat_z_scale->isEditing())
        this->ui->lineEditFloat_z_scale->refresh();
    if (!this->ui->lineEditFloat_x_rotation->isEditing())
    {
        if (this->ui->lineEditFloat_x_rotation->isEnabled())
            this->ui->lineEditFloat_x_rotation->setText(QString::number(glm::degrees(this->ui->lineEditFloat_x_rotation->getValue())));
    }
    if (!this->ui->lineEditFloat_y_rotation->isEditing())
    {
        if (this->ui->lineEditFloat_y_rotation->isEnabled())
            this->ui->lineEditFloat_y_rotation->setText(QString::number(glm::degrees(this->ui->lineEditFloat_y_rotation->getValue())));
    }
    if (!this->ui->lineEditFloat_z_rotation->isEditing())
    {
        if (this->ui->lineEditFloat_z_rotation->isEnabled())
            this->ui->lineEditFloat_z_rotation->setText(QString::number(glm::degrees(this->ui->lineEditFloat_z_rotation->getValue())));
    }

    if (this->exportData.needToInsertOutlineTreeWidget != entt::null)
    {
        this->addGameObjectToOutline(this->exportData.needToInsertOutlineTreeWidget);
        this->exportData.needToInsertOutlineTreeWidget = entt::null;
    }
}

void MainWindow::onFocusChanged(bool& isFocusOnSDL)
{
    if (isFocusOnSDL)
    {
#if USE_WINDOWS
        SetFocus((HWND)this->winId());
        isFocusOnSDL = false;
#endif
    }
}

void MainWindow::embedSDL(WId winId, SDL_Editor_Window* newSDL_window)
{
    this->SDL_editor_window = newSDL_window;
    SDL_Editor_Window_Wrapper_Window* window = (SDL_Editor_Window_Wrapper_Window*)QWindow::fromWinId(winId);
    this->SDLWidget = (SDL_Editor_Window_Wrapper*)(QWidget::createWindowContainer(window));
    this->ui->centralwidget->layout()->addWidget(this->SDLWidget);

    this->SDL_editor_window->bindExportData(this->getExportDataPtr());
}

void MainWindow::getTreeWigetItemInfo(QTreeWidgetItem* item, int column)
{
    OutlineTreeWidgetItem* outlineItem = dynamic_cast<OutlineTreeWidgetItem*>(item);
    if (outlineItem != nullptr)
        outlineItem->click();
    else
        return;
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

    std::string prefixPath = this->projectParser->getProjectDirname() + "/content/texture/";
    // this->ui->comboBox_texture->setCurrentIndex(this->ui->comboBox_texture->findData(QString::fromStdString(prefixPath + meshComponent.textureName)));
}

void MainWindow::openColorDialog()
{
    QColor color = QColorDialog::getColor();
    this->ui->lineEditFloat_R_color->setValue(color.redF());
    this->ui->lineEditFloat_G_color->setValue(color.greenF());
    this->ui->lineEditFloat_B_color->setValue(color.blueF());
    this->updateColorViewer();
}

void MainWindow::compileProject()
{
    if (this->projectParser->getProjectName() == "")
    {
        QMessageBox::warning(this, "Error", "Must load a project before compile.");
        return;
    }
    this->compileProcess.compile(this->projectParser->getProjectDirname());
}

void MainWindow::runProject()
{
    if (this->projectParser->getProjectName() == "")
    {
        QMessageBox::warning(this, "Error", "Must load a project before compile.");
        return;
    }
    this->compileProcess.run(this->projectParser->getProjectName(), this->projectParser->getProjectDirname());
}

void MainWindow::updateColorViewer()
{
    int R = (int)(this->ui->lineEditFloat_R_color->getValue() * 255);
    int G = (int)(this->ui->lineEditFloat_G_color->getValue() * 255);
    int B = (int)(this->ui->lineEditFloat_B_color->getValue() * 255);
    QColor color(R, G, B);
    this->ui->widget_colorViewer->setStyleSheet("background-color: " + color.name() + ";");
    // this->ui->openglWidget->update();
}

void MainWindow::updateTextureViewer()
{
    QString texturePath = this->ui->comboBox_texture->currentData().toString();
    if (texturePath == "")
    {
        this->ui->label_textureViewer->setPixmap(QPixmap());
        return;
    }
    QPixmap pixmap = QPixmap(texturePath);
    pixmap = pixmap.scaled(this->ui->label_textureViewer->width(), this->ui->label_textureViewer->height(), Qt::KeepAspectRatio);
    this->ui->label_textureViewer->setPixmap(pixmap);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->SDL_editor_window->running = false;
    QMainWindow::closeEvent(event);
}

void MainWindow::clearOutline()
{
    while (this->actorLevel->takeChild(0) != nullptr)
        ;
}

void MainWindow::resetTextureComboBox()
{
    this->ui->comboBox_texture->clear();
    std::filesystem::directory_iterator fileList(this->projectParser->getProjectDirname() + "/content/texture");
    this->ui->comboBox_texture->addItem("None", "");
    for (auto& file: fileList)
    {
        this->ui->comboBox_texture->addItem(QString::fromStdString(file.path().filename().u8string()), QString::fromStdString(file.path().u8string()));
    }
}

void MainWindow::addGameObjectToOutline(entt::entity entityID)
{
    OutlineTreeWidgetItem *item = new OutlineTreeWidgetItem(this->actorLevel);
    GameEngine::TagComponent& tagComponent = GameEngine::globalScene->queryActorComponent<GameEngine::TagComponent>(entityID);
    item->setText(0, QString::fromStdString(tagComponent.tagName));
    item->setEntityID(entityID);
    this->actorLevel->addChild(item);

    this->actorLevel->insertItem(item);
}

void MainWindow::resetGameObjectOutline()
{
    this->clearOutline();
    std::vector<entt::entity> entities = EditorScene::getAllActors();
    for (entt::entity entity: entities)
    {
        OutlineTreeWidgetItem* item = new OutlineTreeWidgetItem(this->actorLevel);
        GameEngine::TagComponent& tagComponent = GameEngine::globalScene->queryActorComponent<GameEngine::TagComponent>(entity);
        item->setText(0, QString::fromStdString(tagComponent.tagName));
        item->setEntityID(entity);
        this->actorLevel->addChild(item);
    }
    this->actorLevel->resetItemsVec();
}

void MainWindow::openProject()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open project"), QDir::homePath(), tr("*.gproject"));
    if (path.size() == 0)
        return;
    this->projectParser->load(path.toStdString().c_str());
    this->ui->contentBrowserPanel->setPath(this->projectParser->getProjectDirname() + "/content");
    this->ui->contentBrowserPanel->reset();
    qDebug("Load project success.\n");
    qDebug("Current project: %s.\n", this->projectParser->getProjectName().c_str());
    
    std::string mapPath = this->projectParser->getProjectDirname() + "/content/scene/" + this->projectParser->getProjectName() + ".map";
    if (std::filesystem::exists(mapPath))
    {
        qDebug("Found scene data in %s.\n", mapPath.c_str());
        GameEngine::SceneSerializer sceneSerializer;
        if (sceneSerializer.deserialize(mapPath))
            qDebug("Load scene success.\n");
        else
            qCritical("Fail to load scene.\n");
    }
    else
        qDebug("Scene data not found.\n");
    this->resetGameObjectOutline();
    this->resetTextureComboBox();
}

void MainWindow::saveScene()
{
    if (this->projectParser->getProjectName() == "")
    {
        QMessageBox::warning(this, "Error", "Must load a project before save.");
        return;
    }
    GameEngine::SceneSerializer sceneSerializer;
    sceneSerializer.serialize(this->projectParser->getProjectDirname() + "/content/scene/" + this->projectParser->getProjectName() + ".map");
    qDebug("Save scene in %s\n", (this->projectParser->getProjectDirname() + "/content/scene/" + this->projectParser->getProjectName() + ".map").c_str());
}

void MainWindow::parseOutput()
{
    textBrowserInsert(this->ui->lineEdit->text() + "\n");
    this->ui->lineEdit->clear();
}