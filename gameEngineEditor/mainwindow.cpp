#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWindow>
#include "Component/Component.h"
#include "Core/Platform.h"
#include "plugins/QCollapsibleWidget.h"
#include "plugins/LineEditFloat.h"
#include "ComponentBrowserWidget.h"
#include <QVBoxLayout>
#if USE_WINDOWS
    #include <winuser.h>
    #include <windows.h>
    #include <dwmapi.h>
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
    , border(10)
{
    ui->setupUi(this);

    //titlebar and borderless window
    this->setWindowFlags(Qt::FramelessWindowHint);

#ifdef Q_OS_WIN
    SetWindowLongPtr((HWND)this->winId(), GWL_STYLE, GetWindowLongPtr((HWND)this->winId(), GWL_STYLE) | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    const MARGINS shadow = {1, 1, 1, 1};
    DwmExtendFrameIntoClientArea((HWND)this->winId(), &shadow);
#endif

    connect(this->ui->pushButton_close, &QPushButton::clicked, this, &MainWindow::onCloseClick);
    connect(this->ui->pushButton_expand, &QPushButton::clicked, this, &MainWindow::onExpandClick);
    connect(this->ui->pushButton_minimize, &QPushButton::clicked, this, &MainWindow::onMinimizeClick);
    this->initTitlebar();
    //
    this->initToolbar();

    this->initAddComponentToolButton();

    this->setAttribute(Qt::WA_Hover);

    QFile qssFile("./qss/gameEngineEditor_ui.qss");
    qssFile.open(QFile::ReadOnly);
    QString qss = QString::fromUtf8(qssFile.readAll());
    this->setStyleSheet(qss);
    qssFile.close();

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

    connect(this->ui->treeWidget, &QTreeWidget::itemClicked, this, &MainWindow::getTreeWigetItemInfo);
    
    this->ui->scrollAreaWidgetContents_detail->layout()->setAlignment(Qt::AlignTop);
    this->resizeDocks({this->ui->dockWidgetLeft}, {this->ui->scrollAreaWidgetContents_detail->width() + 20}, Qt::Horizontal);
    
    //bind tiemr to outline if there is an entity need to insert to outline
    connect(&(this->timer), &QTimer::timeout, this, &MainWindow::updateOutline);
    connect(this->ui->treeWidget, &OutlineTreeWidget::onSetSelectedItemToNull, [this](){
        this->hideAllDetail();
    });
    this->timer.start(41);

    //export data
    this->exportData.outlineTreeWidget = this->ui->treeWidget;
    this->exportData.actorCollection = this->actorLevel;

    // init detail connection
    this->initDetailConnection();
    //end init detail connection
    
    this->hideAllDetail();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->projectParser;
}

void MainWindow::initTitlebar()
{
    QMenuBar* menubar = new QMenuBar();
    menubar->setObjectName("menubar");
    QMenu* fileMenu = new QMenu("File", menubar);
        QAction* actionSave = new QAction("Save", fileMenu);
        QAction* actionOpen = new QAction("Open", fileMenu);
        connect(actionOpen, &QAction::triggered, this, &MainWindow::openProject);
        connect(actionSave, &QAction::triggered, this, &MainWindow::saveScene);
        fileMenu->addAction(actionSave);
        fileMenu->addAction(actionOpen);
    menubar->addMenu(fileMenu);
    QMenu* settingMenu = new QMenu("Setting", menubar);
    menubar->addMenu(settingMenu);
    QMenu* helpMenu = new QMenu("Help", menubar);
    menubar->addMenu(helpMenu);
    menubar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->ui->menubarLayout->setAlignment(Qt::AlignCenter);
    this->ui->menubarLayout->addWidget(menubar);
    
    connect(this->ui->titlebar, &Titlebar::onMousePressEventSignal, [=](){
        this->window()->windowHandle()->startSystemMove();
    });
    connect(this->ui->titlebar, &Titlebar::onMouseDoubleClickEventSignal, [=](){
        this->onExpandClick();
    });
    // hit border event
    connect(this->ui->titlebar, &Titlebar::onHitBorderSignal, this, &MainWindow::onHitBorder);
    this->ui->treeWidget->bindMainWindowPtr(this);
    connect(this->ui->treeWidget, &OutlineTreeWidget::onHitBorderSignal, this, &MainWindow::onHitBorder);

    
}

void MainWindow::initToolbar()
{
    QWidget* leftSpacer = new QWidget(this);
    QWidget* rightSpacer = new QWidget(this);
    leftSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rightSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QToolBar* toolbar = new QToolBar(this);
    toolbar->setObjectName("toolbar");
    toolbar->addWidget(leftSpacer);
    QAction* actionCompile = new QAction(toolbar);
    QIcon iconCompile;
    iconCompile.addFile(QString::fromUtf8(":/icon/icon/compile.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionCompile->setIcon(iconCompile);
    this->actionRun = new QAction(toolbar);
    QIcon iconRun;
    iconRun.addFile(QString::fromUtf8(":/icon/icon/play.png"), QSize(), QIcon::Normal, QIcon::Off);
    this->actionRun->setIcon(iconRun);
    
    toolbar->addAction(actionCompile);
    toolbar->addAction(actionRun);
    connect(actionCompile, &QAction::triggered, this, &MainWindow::compileProject);
    connect(actionRun, &QAction::triggered, [this]() {
        if (this->SDL_editor_window->sceneState == SceneState::Edit)
        {
            QIcon iconRun;
            iconRun.addFile(QString::fromUtf8(":/icon/icon/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
            this->actionRun->setIcon(iconRun);
            this->SDL_editor_window->onScenePlay();
        }
        else if (this->SDL_editor_window->sceneState == SceneState::Play)
        {
            QIcon iconRun;
            iconRun.addFile(QString::fromUtf8(":/icon/icon/play.png"), QSize(), QIcon::Normal, QIcon::Off);
            this->actionRun->setIcon(iconRun);
            this->SDL_editor_window->onSceneStop();
        }
    });
    // connect(actionRun, &QAction::triggered, this, &MainWindow::runProject);
    
    toolbar->addWidget(rightSpacer);
    this->ui->toolbarLayout->addWidget(toolbar);
}

void MainWindow::initAddComponentToolButton()
{
    ComponentBrowserButton* componentBrowserButton = new ComponentBrowserButton(this->ui->widget_addComponentWrap);
    this->ui->widget_addComponentWrap->layout()->addWidget(componentBrowserButton);
    componentBrowserButton->getPopupWidget()->bindExportDataPtr(&(this->exportData));

    connect(componentBrowserButton->getPopupWidget(), &ComponentBrowserWidget::onAddedComponent, [this](){
        this->updateDetail();
    });
}

void MainWindow::initDetailConnection()
{
    // init detail connection
    
    // mesh component(texture)
    connect(this->ui->comboBox_texture, &QComboBox::currentIndexChanged, this, &MainWindow::updateTextureViewer);
    
    // mesh component(color)
    connect(this->ui->pushButton_colorPicker, &QPushButton::clicked, this, &MainWindow::openColorDialog);
    connect(this->ui->lineEditFloat_R_color, &LineEditFloat::editingFinished, this, &MainWindow::updateColorViewer);
    connect(this->ui->lineEditFloat_G_color, &LineEditFloat::editingFinished, this, &MainWindow::updateColorViewer);
    connect(this->ui->lineEditFloat_B_color, &LineEditFloat::editingFinished, this, &MainWindow::updateColorViewer);

    // camera component
    connect(this->ui->checkBox_isPrimary, &QCheckBox::stateChanged, this, &MainWindow::onIsPrimaryStateChanged);
}

#ifdef Q_OS_WIN
bool MainWindow::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
    MSG* msg = static_cast<MSG*>(message);

    if (!this->isVisible())
        return false;
    HWND hwnd = (HWND)this->winId();
    
    switch (msg->message)
    {
    case WM_NCCALCSIZE:
    {
        if (msg->lParam)
        {
            NCCALCSIZE_PARAMS* sz = (NCCALCSIZE_PARAMS*)msg->lParam;
            // sz->rgrc[0].top -= borderThicknessTop;
            // sz->rgrc[0].left += 1;
            // sz->rgrc[0].right += 1;
            sz->rgrc[0].bottom += 1; //為了讓非客戶區大於客戶區一點點，又只有bottom不會出現奇怪的白線1px
        }
        // break;
        *result = 0;
        return true;
    }
    default:
        break;
    }
    return QMainWindow::nativeEvent(eventType, message, result);
}
#endif

void MainWindow::updateOutline()
{
    if (this->exportData.needToInsertOutlineTreeWidget != entt::null)
    {
        this->addGameObjectToOutline(this->exportData.needToInsertOutlineTreeWidget);
        this->exportData.needToInsertOutlineTreeWidget = entt::null;
    }
}

void MainWindow::onFocusChanged(bool& isFocusOnSDL)
{
#if USE_WINDOWS    
    if (isFocusOnSDL)
    {
        SetFocus((HWND)this->winId());
        isFocusOnSDL = false;
    }
#endif
}

void MainWindow::onCloseClick()
{
    this->close();
}

void MainWindow::onExpandClick()
{
    static QIcon iconExpandWindowMin;
    static QIcon iconExpandWindowMax;
    //init僅會執行一次
    static bool init = [=](){
        iconExpandWindowMin.addFile(QString::fromUtf8(":/icon/icon/expand-window-min.png"), QSize(), QIcon::Normal, QIcon::Off);
        iconExpandWindowMax.addFile(QString::fromUtf8(":/icon/icon/expand-window-max.png"), QSize(), QIcon::Normal, QIcon::Off);
        return true;
    }();
    
    if (this->isMaximized())
    {
        this->ToNormal();
        this->ui->pushButton_expand->setIcon(iconExpandWindowMax);
    }
    else
    {
        this->ToMaximize();
        this->ui->pushButton_expand->setIcon(iconExpandWindowMin);
    }
}

void MainWindow::onMinimizeClick()
{
    this->showMinimized();
}

void MainWindow::onHitBorder(QPoint pos)
{
    Qt::Edges edges;
    if (pos.x() > this->width() - border)
        edges |= Qt::RightEdge;
    if (pos.x() < border)
        edges |= Qt::LeftEdge;
    if (pos.y() > this->height() - border)
        edges |= Qt::BottomEdge;
    if (pos.y() < border)
        edges |= Qt::TopEdge;
    if (edges != 0) 
    {
        // Note: on Mac, this will return false which means isn't supported.
        this->windowHandle()->startSystemResize(edges);
    }
}

void MainWindow::onAddComponent()
{
    // ComponentBrowserDialog::getComponent();
}

void MainWindow::embedSDL(WId winId, SDL_Editor_Window* newSDL_window)
{
    this->SDL_editor_window = newSDL_window;
    QWindow* window = QWindow::fromWinId(winId);
    this->SDLWidget = (SDL_Editor_Window_Wrapper*)(QWidget::createWindowContainer(window));
    this->ui->SDL_windgetWrap->layout()->addWidget(this->SDLWidget);

    this->SDL_editor_window->bindExportData(this->getExportDataPtr());
}

void MainWindow::getTreeWigetItemInfo(QTreeWidgetItem* item, int column)
{
    OutlineTreeWidgetItem* outlineItem = dynamic_cast<OutlineTreeWidgetItem*>(item);
    if (outlineItem != nullptr)
        outlineItem->click();
    else
        return;
    this->updateDetail();
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
}

void MainWindow::updateTextureViewer()
{
    entt::entity entityID = this->ui->treeWidget->getSelectedEntity();
    if (entityID == entt::null)
        return;
    QString texturePath = this->ui->comboBox_texture->currentData().toString();
    if (texturePath == "")
    {
        this->ui->label_textureViewer->setPixmap(QPixmap());
        GameEngine::MeshComponent& meshComponent = GameEngine::globalScene->queryActorComponent<GameEngine::MeshComponent>(entityID);
        if (meshComponent.texture != nullptr)
        {
            delete meshComponent.texture;
            meshComponent.texture = nullptr;
        }
        return;
    }
    QPixmap pixmap = QPixmap(texturePath);
    pixmap = pixmap.scaled(this->ui->label_textureViewer->width(), this->ui->label_textureViewer->height(), Qt::KeepAspectRatio);
    this->ui->label_textureViewer->setPixmap(pixmap);
    if (GameEngine::globalScene->actorHasComponent<GameEngine::MeshComponent>(entityID))
    {
        GameEngine::MeshComponent& meshComponent = GameEngine::globalScene->queryActorComponent<GameEngine::MeshComponent>(entityID);
        if (meshComponent.texture == nullptr)
        {
            meshComponent.texture = new GameEngine::Texture();
        }
        // meshComponent.texture->load("assets/texture/test.png", GL_NEAREST);
        GameEngine::GEngine->textureManager->createTexture("D:/code/cpp/gameEngine/build/TestGame/assets/texture/test.png", meshComponent.texture, GL_NEAREST);
    }
}

bool MainWindow::event(QEvent *event)
{
    static constexpr int border = 6;

    if (event->type() == QEvent::HoverMove)
    {
        QPoint pos = dynamic_cast<QHoverEvent*>(event)->position().toPoint();
        if (pos.y() > this->height() - border)
        {
            if (pos.x() < border)
                this->setCursor(Qt::SizeBDiagCursor);
            else if (pos.x() > this->width() - border)
                this->setCursor(Qt::SizeFDiagCursor);
            else
                this->setCursor(Qt::SizeVerCursor);
        }
        else if (pos.y() < border)
        {
            if (pos.x() < border)
                this->setCursor(Qt::SizeFDiagCursor);
            else if (pos.x() > this->width() - border)
                this->setCursor(Qt::SizeBDiagCursor);
            else
                this->setCursor(Qt::SizeVerCursor);
        }
        else if ((pos.y() > border)
                    &&
                (((pos.x() > this->width() - border) || (pos.x() < border))))
        {
            this->setCursor(Qt::SizeHorCursor);
        }
        else
            this->setCursor(Qt::ArrowCursor);
    }
    else if (event->type() == QEvent::MouseButtonPress) 
    {
        if (dynamic_cast<QMouseEvent*>(event)->button() != Qt::LeftButton)
            return QMainWindow::event(event);
        QPoint pos = dynamic_cast<QMouseEvent*>(event)->position().toPoint();
        this->onHitBorder(pos);
    }

    return QMainWindow::event(event);
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
    std::filesystem::directory_iterator fileList(this->projectParser->getProjectDirname() + "/assets/texture");
    this->ui->comboBox_texture->addItem("None", "");
    for (auto& file: fileList)
    {
        qInfo() << QString::fromStdString(file.path().u8string()) <<'\n';
        this->ui->comboBox_texture->addItem(QString::fromStdString(file.path().filename().u8string()), QString::fromStdString(file.path().u8string()));
    }
}

void MainWindow::ToMaximize()
{
#ifdef Q_OS_WIN
    SetWindowLongPtr((HWND)this->winId(), GWL_STYLE, GetWindowLongPtr((HWND)this->winId(), GWL_STYLE) & ~(WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION));
#endif
    this->showMaximized();
}

void MainWindow::ToNormal()
{
#ifdef Q_OS_WIN
    SetWindowLongPtr((HWND)this->winId(), GWL_STYLE, GetWindowLongPtr((HWND)this->winId(), GWL_STYLE) | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    const MARGINS shadow = {1, 1, 1, 1};
    DwmExtendFrameIntoClientArea((HWND)this->winId(), &shadow);
#endif
    this->showNormal();
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
    this->ui->contentBrowserPanel->setPath(this->projectParser->getProjectDirname() + "/assets");
    this->ui->contentBrowserPanel->reset();
    qDebug("Load project success.\n");
    qDebug("Current project: %s.\n", this->projectParser->getProjectName().c_str());
    
    std::string mapPath = this->projectParser->getProjectDirname() + "/assets/scene/" + this->projectParser->getProjectName() + ".map";
    if (std::filesystem::exists(mapPath))
    {
        qDebug("Found scene data in %s.\n", mapPath.c_str());
        GameEngine::SceneSerializer sceneSerializer;
        if (sceneSerializer.deserialize(mapPath))
        {
            qDebug("Load scene success.\n");
        }
        else
            qCritical("Fail to load scene.\n");
    }
    else
        qDebug("Scene data not found.\n");
    this->resetGameObjectOutline();
    this->resetTextureComboBox();
    GameEngine::GEngine->setWorkingDirname(this->projectParser->getProjectDirname());

    GameEngine::Actor actor0 = {(entt::entity)0};
    actor0.addComponent<GameEngine::Rigidbody2DComponent>();
    actor0.addComponent<GameEngine::BoxCollider2DComponent>();

    GameEngine::Rigidbody2DComponent& rigidbody2DComponent0 = actor0.getComponent<GameEngine::Rigidbody2DComponent>();
    rigidbody2DComponent0.type = GameEngine::Rigidbody2DComponent::BodyType::Dynamic;

    GameEngine::Actor actor1 = {(entt::entity)1};
    actor1.addComponent<GameEngine::Rigidbody2DComponent>();
    actor1.addComponent<GameEngine::BoxCollider2DComponent>();

    GameEngine::Rigidbody2DComponent& rigidbody2DComponent1 = actor1.getComponent<GameEngine::Rigidbody2DComponent>();
    rigidbody2DComponent1.type = GameEngine::Rigidbody2DComponent::BodyType::Static;
}

void MainWindow::saveScene()
{
    if (this->projectParser->getProjectName() == "")
    {
        QMessageBox::warning(this, "Error", "Must load a project before save.");
        return;
    }
    GameEngine::SceneSerializer sceneSerializer;
    sceneSerializer.serialize(this->projectParser->getProjectDirname() + "/assets/scene/" + this->projectParser->getProjectName() + ".map");
    qDebug("Save scene in %s\n", (this->projectParser->getProjectDirname() + "/assets/scene/" + this->projectParser->getProjectName() + ".map").c_str());
}

void MainWindow::parseOutput()
{
    textBrowserInsert(this->ui->lineEdit->text() + "\n");
    this->ui->lineEdit->clear();
}

//以下為detail中加入對應widget的function

template<>
void MainWindow::pushComponentProperty<GameEngine::TransformComponent>(const entt::entity& entityID)
{
    GameEngine::TransformComponent& transformComponent = GameEngine::globalScene->queryActorComponent<GameEngine::TransformComponent>(entityID);
    this->ui->lineEditFloat_x_position->bind(&transformComponent.translation.x);
    this->ui->lineEditFloat_y_position->bind(&transformComponent.translation.y);
    this->ui->lineEditFloat_z_position->bind(&transformComponent.translation.z);
    this->ui->lineEditFloat_x_scale->bind(&transformComponent.scale.x);
    this->ui->lineEditFloat_y_scale->bind(&transformComponent.scale.y);
    this->ui->lineEditFloat_z_scale->bind(&transformComponent.scale.z);
    this->ui->lineEditFloat_x_rotation->bind(&transformComponent.rotation.x);
    this->ui->lineEditFloat_y_rotation->bind(&transformComponent.rotation.y);
    this->ui->lineEditFloat_z_rotation->bind(&transformComponent.rotation.z);

    connect(&(this->timer), &QTimer::timeout, this, &MainWindow::onTransformUpdate);

    this->ui->qCollapsibleWidget_transform->show();
}

template<>
void MainWindow::pushComponentProperty<GameEngine::MeshComponent>(const entt::entity& entityID)
{
    GameEngine::MeshComponent& meshComponent = GameEngine::globalScene->queryActorComponent<GameEngine::MeshComponent>(entityID);
    this->ui->lineEditFloat_R_color->bind(&meshComponent.color.r);
    this->ui->lineEditFloat_G_color->bind(&meshComponent.color.g);
    this->ui->lineEditFloat_B_color->bind(&meshComponent.color.b);
    this->ui->pushButton_colorPicker->setEnabled(true);
    this->updateColorViewer();

    this->ui->qCollapsibleWidget_color->show();

    this->ui->label_textureViewer->setStyleSheet("background: #000000;");
    if (meshComponent.texture != nullptr)
    {
        this->ui->comboBox_texture->setCurrentIndex(this->ui->comboBox_texture->findText(QString::fromStdString(GameEngine::GEngine->textureManager->getTextureFileName(meshComponent.texture->getTextureID()))));
    }
    else
        this->ui->comboBox_texture->setCurrentIndex(this->ui->comboBox_texture->findText("None"));
    
    this->ui->qCollapsibleWidget_texture->show();
}

template<>
void MainWindow::pushComponentProperty<GameEngine::CameraComponent>(const entt::entity& entityID)
{
    this->ui->qCollapsibleWidget_camera->show();
}

template<>
void MainWindow::pushComponentProperty<GameEngine::Rigidbody2DComponent>(const entt::entity& entityID)
{
    this->ui->qCollapsibleWidget_rigidbody2D->show();
}

template<>
void MainWindow::pushComponentProperty<GameEngine::BoxCollider2DComponent>(const entt::entity& entityID)
{
    GameEngine::BoxCollider2DComponent& boxCollider2DComponent = GameEngine::globalScene->queryActorComponent<GameEngine::BoxCollider2DComponent>(entityID);

    this->ui->lineEditFloat_boxCollider2D_offset_x->bind(&boxCollider2DComponent.offset.x);
    this->ui->lineEditFloat_boxCollider2D_offset_y->bind(&boxCollider2DComponent.offset.y);
    this->ui->lineEditFloat_boxCollider2D_size_x->bind(&boxCollider2DComponent.size.x);
    this->ui->lineEditFloat_boxCollider2D_size_y->bind(&boxCollider2DComponent.size.y);
    this->ui->lineEditFloat_boxCollider2D_density->bind(&boxCollider2DComponent.density);
    this->ui->lineEditFloat_boxCollider2D_friction->bind(&boxCollider2DComponent.friction);
    this->ui->lineEditFloat_boxCollider2D_restitution->bind(&boxCollider2DComponent.restitution);
    this->ui->lineEditFloat_boxCollider2D_restitutionThreshold->bind(&boxCollider2DComponent.restitutionThreshold);

    this->ui->qCollapsibleWidget_boxCollider2D->show();
}

void MainWindow::onTransformUpdate()
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
}

void MainWindow::onIsPrimaryStateChanged()
{
    entt::entity entityID = this->ui->treeWidget->getSelectedEntity();
    if (entityID == entt::null)
        return;
    GameEngine::CameraComponent& cameraComponent = GameEngine::globalScene->queryActorComponent<GameEngine::CameraComponent>(entityID);
    cameraComponent.primary = this->ui->checkBox_isPrimary->isChecked();
}

void MainWindow::hideAllDetail()
{
    if (this->ui->qCollapsibleWidget_transform->isVisible())
    {
        disconnect(&(this->timer), &QTimer::timeout, this, &MainWindow::onTransformUpdate);
        this->ui->qCollapsibleWidget_transform->hide();
    }
    QLayout* layout = this->ui->scrollAreaWidgetContents_detail->layout();
    QWidget* childWidget;
    //-1 for verticalSpacer
    for (int i = 0; i < layout->count() - 1; ++i)
    {
        childWidget = layout->itemAt(i)->widget();
        childWidget->hide();
    }

    // this->ui->qCollapsibleWidget_rigidbody2D->show();
    // this->ui->qCollapsibleWidget_boxCollider2D->show();
}

void MainWindow::updateDetail()
{
    this->hideAllDetail();
    entt::entity entityID = this->ui->treeWidget->getSelectedEntity();
    if (entityID == entt::null)
        return;
    this->ui->widget_addComponentWrap->show();
    GameEngine::Actor actor(entityID);
    if (actor.hasComponent<GameEngine::TransformComponent>())
        this->pushComponentProperty<GameEngine::TransformComponent>(entityID);
    if (actor.hasComponent<GameEngine::MeshComponent>())
        this->pushComponentProperty<GameEngine::MeshComponent>(entityID);
    if (actor.hasComponent<GameEngine::CameraComponent>())
        this->pushComponentProperty<GameEngine::CameraComponent>(entityID);
    if (actor.hasComponent<GameEngine::Rigidbody2DComponent>())
        this->pushComponentProperty<GameEngine::Rigidbody2DComponent>(entityID);
    if (actor.hasComponent<GameEngine::BoxCollider2DComponent>())
        this->pushComponentProperty<GameEngine::BoxCollider2DComponent>(entityID);
}


