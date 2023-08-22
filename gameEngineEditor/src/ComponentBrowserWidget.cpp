#include "ComponentBrowserWidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QApplication>
#include <QResizeEvent>
#include <memory.h>
#include "Core/Assert.h"

bool ComponentBrowserTriePair::operator<(const ComponentBrowserTriePair &other) const
{
    return (this->data < other.data);
}

ComponentBrowserTrieNode::ComponentBrowserTrieNode()
    : buttonPtr(nullptr)
    , size(0U)
{
    this->nexts = (ComponentBrowserTriePair*)malloc(sizeof(ComponentBrowserTriePair));
}

int ComponentBrowserTrieNode::binarySearch(char target)
{
    int left = 0;
    int right = this->size - 1;
    int mid;
    while (left <= right)
    {
        mid = (left + right) >> 1;
        if(this->nexts[mid].data > target)
            right = mid - 1;
        else if (this->nexts[mid].data < target)
            left = mid + 1;
        else 
            return mid;
    }
    return -1;
}

void ComponentBrowserTrieNode::dfs(std::vector<QToolButton*> &res)
{
    if (this->isWord())
        res.push_back(this->buttonPtr);
    for (int i = 0; i < this->size; ++i)
    {
        this->nexts[i].trieNodePtr->dfs(res);
    }
    return;
}

bool ComponentBrowserTrieNode::isWord() const
{
    return (this->buttonPtr != nullptr);
}

void ComponentBrowserTrieNode::insert(const std::string& str, QToolButton* targetPtr)
{
    ComponentBrowserTrieNode* current = this;
    int index = 0;
    char target;
    for (int strIndex = 0; strIndex < str.size(); ++strIndex)
    {
        //只存小寫字母或一些_、&、!等符號
        target = tolower(str[strIndex]);
        index = current->binarySearch(target);        
        if (index == -1)
        {
            //代表需要擴充空間
            ComponentBrowserTriePair newPair = {target, new ComponentBrowserTrieNode()};
            
            //平移並插入
            ++current->size;
            current->nexts = (ComponentBrowserTriePair*)realloc(current->nexts, sizeof(ComponentBrowserTriePair) * current->size);
            GAME_ENGINE_ASSERT(current->nexts != NULL, "Can't realloc more memory");
            
            auto it = std::lower_bound(current->nexts, current->nexts + (current->size - 1), newPair);
            if (it == current->nexts + (current->size - 1))
            {
                //代表在最尾端
                current->nexts[current->size - 1] = newPair;
            }
            else
            {
                int insertPos = it - current->nexts;
                for (int i = current->size - 1; i > insertPos; --i)
                    current->nexts[i] = current->nexts[i - 1];
                current->nexts[insertPos] = newPair;
            }
            current = newPair.trieNodePtr;
        }
        else
        {
            current = current->nexts[index].trieNodePtr;
        }
        if (strIndex == str.size() - 1)
            current->buttonPtr = targetPtr;
    }
    
}

bool ComponentBrowserTrieNode::queryNext(char target)
{
    return (this->binarySearch(target) != -1);
}

//ComponentBrowserTrie
ComponentBrowserTrie::ComponentBrowserTrie()
    : root(new ComponentBrowserTrieNode())
{
}

void ComponentBrowserTrie::insert(const std::string& str, QToolButton* targetPtr)
{
    this->root->insert(str, targetPtr);
}

std::vector<QToolButton*> ComponentBrowserTrie::getAllStartWith(const std::string& prefix) const
{
    std::vector<QToolButton*> res;
    ComponentBrowserTrieNode* current = this->root;
    int index;
    for (int i = 0; i < prefix.size(); i++)
    {
        index = current->binarySearch(tolower(prefix[i]));
        if (index != -1)
            current = current->nexts[index].trieNodePtr;
        else //代表沒有符合前綴的資料
            return res;
    }
    current->dfs(res);
    return res;
}

//ComponentBrowserStackedWidget
ComponentBrowserStackedWidget::ComponentBrowserStackedWidget(QWidget* parent)
    : QStackedWidget(parent)
{
}

QSize ComponentBrowserStackedWidget::sizeHint() const
{
    return this->currentWidget()->sizeHint();
}

QSize ComponentBrowserStackedWidget::minimumSizeHint() const
{
    return this->currentWidget()->minimumSizeHint();
}

//ComponentBrowserWidget
ComponentBrowserWidget::ComponentBrowserWidget(QMenu* ptr, QWidget *parent)
    : QWidget(parent)
    , trie(new ComponentBrowserTrie())
    , menuPtr(ptr)
    , exportDataPtr(nullptr)
{
    this->setupUI();
}

void ComponentBrowserWidget::bindExportDataPtr(GameEngineEditor::ExportData *ptr)
{
    this->exportDataPtr = ptr;
}

void ComponentBrowserWidget::setSelectedComponentType(GameEngine::GameEngineComponentType type)
{
    this->selectedComponentType = type;
}

void ComponentBrowserWidget::swithToHomePage()
{
    if (this->componentBrowserStackedWidget->count() > 1)
    {
        for (int i = this->componentBrowserStackedWidget->count() - 1; i > 0; --i)
        {
            QWidget* widget = this->componentBrowserStackedWidget->widget(i);
            this->componentBrowserStackedWidget->removeWidget(widget);
            widget->deleteLater();
        }
        this->componentBrowserStackedWidget->setCurrentIndex(0);
    }

    this->browserWrap->adjustSize();
    this->componentBrowserStackedWidget->adjustSize();
    this->adjustSize();
    // QResizeEvent re(QSize(), this->menuPtr->size());
    // qApp->sendEvent(this->menuPtr, &re);
    // this->menuPtr->adjustSize();
}

static QToolButton* createToolButton(ComponentBrowserWidget* browserWidget, QWidget* widget, QVBoxLayout* layout, const std::string& buttonText, GameEngine::GameEngineComponentType type)
{
    QToolButton* button = new QToolButton(widget);
    button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    button->setText(QString::fromStdString(buttonText));
    layout->addWidget(button);
    QObject::connect(button, &QToolButton::clicked, [browserWidget, type](){
        browserWidget->setSelectedComponentType(type);
        browserWidget->onToolButtonClick();
    });
    return button;
}

static QToolButton* createToolButton(QWidget* widget, QVBoxLayout* layout, const std::string& buttonText, std::function<void()> func)
{
    QToolButton* button = new QToolButton(widget);
    button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    button->setText(QString::fromStdString(buttonText));
    layout->addWidget(button);
    QObject::connect(button, &QToolButton::clicked, func);
    return button;
}

void ComponentBrowserWidget::entityAddComponent(entt::entity &entityID, GameEngine::GameEngineComponentType type)
{
    GameEngine::Actor actor(entityID, GameEngine::globalScene);
    bool isAddedComponent = true;
    switch (type)
    {
    case GameEngine::GameEngineComponentType::TransformComponent:
        actor.addComponent<GameEngine::TransformComponent>();
        break;
    case GameEngine::GameEngineComponentType::MeshComponent:
        actor.addComponent<GameEngine::MeshComponent>();
        break;
    case GameEngine::GameEngineComponentType::CameraComponent:
        actor.addComponent<GameEngine::CameraComponent>();
        break;
    case GameEngine::GameEngineComponentType::Rigidbody2DComponent:
        actor.addComponent<GameEngine::Rigidbody2DComponent>();
        break;
    case GameEngine::GameEngineComponentType::BoxCollider2DComponent:
        actor.addComponent<GameEngine::BoxCollider2DComponent>();
        break;
    case GameEngine::GameEngineComponentType::ScriptComponent:
        actor.addComponent<GameEngine::ScriptComponent>();
        break;
    default:
        isAddedComponent = false;
        break;
    }

    if (isAddedComponent)
        emit this->onAddedComponent();
}

void ComponentBrowserWidget::setupUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    this->setLayout(layout);

    //search bar
    this->searchBar = new QLineEdit(this);
    this->searchBar->addAction(QIcon(":/icon/icon/search.png"), QLineEdit::LeadingPosition);
    this->searchBar->setClearButtonEnabled(true);
    this->searchBar->setPlaceholderText("Search...");
    this->searchBar->setObjectName("searchBar");
    layout->addWidget(this->searchBar);

    // componentBrowser
    this->componentBrowserStackedWidget = new ComponentBrowserStackedWidget(this);

    this->browserWrap = new QWidget(this->componentBrowserStackedWidget);
    this->browserWrap->setObjectName("browserWrap");

    this->browserLayout = new QVBoxLayout(this->browserWrap);
    this->browserLayout->setContentsMargins(0, 0, 0, 0);
    this->browserLayout->setSpacing(0);
    this->browserWrap->setLayout(this->browserLayout);

    QToolButton* transformButton = createToolButton(this, this->browserWrap, this->browserLayout, "Transform", GameEngine::GameEngineComponentType::TransformComponent);
    this->trie->insert("Transform", transformButton);

    QToolButton* meshButton = createToolButton(this, this->browserWrap, this->browserLayout, "Mesh", GameEngine::GameEngineComponentType::MeshComponent);
    this->trie->insert("Mesh", meshButton);

    QToolButton* cameraButton = createToolButton(this, this->browserWrap, this->browserLayout, "Camera", GameEngine::GameEngineComponentType::CameraComponent);
    this->trie->insert("Camera", cameraButton);

    QToolButton* physicsButton = createToolButton(this->browserWrap, this->browserLayout, "Physics2D", []()->void{});
    this->trie->insert("physics2D", physicsButton);
    this->setupPhysicsWidget(physicsButton);
    connect(physicsButton, QToolButton::clicked, [this, physicsButton]() {
        QWidget* physicsWidget = this->setupPhysicsWidget(physicsButton);
        this->componentBrowserStackedWidget->addWidget(physicsWidget);
        this->componentBrowserStackedWidget->setCurrentIndex(1);
        
        physicsWidget->adjustSize();
        this->filterComponentBrowser();
    });

    QToolButton* scriptButton = createToolButton(this, this->browserWrap, this->browserLayout, "Script", GameEngine::GameEngineComponentType::ScriptComponent);
    this->trie->insert("Script", scriptButton);

    this->componentBrowserStackedWidget->addWidget(this->browserWrap);

    layout->addWidget(this->componentBrowserStackedWidget);

    connect(this->searchBar, &QLineEdit::textChanged, this, &ComponentBrowserWidget::filterComponentBrowser);

    connect(this, &ComponentBrowserWidget::onAddComponentSignal, [this](){
        entt::entity entityID = this->exportDataPtr->outlineTreeWidget->getSelectedEntity();
        if (entityID != entt::null)
        {
            if (this->selectedComponentType != GameEngine::GameEngineComponentType::Null)
            {
                entityAddComponent(entityID, this->selectedComponentType);
                this->selectedComponentType = GameEngine::GameEngineComponentType::Null;
            }
        }
    });
}

QWidget *ComponentBrowserWidget::setupPhysicsWidget(QToolButton* physicsButton)
{
    QWidget* physicsWidget = new QWidget(this->componentBrowserStackedWidget);
    QVBoxLayout* physicsLayout = new QVBoxLayout(physicsWidget);
    physicsLayout->setContentsMargins(0, 0, 0, 0);
    physicsLayout->setSpacing(0);
    physicsLayout->addLayout(physicsLayout);

    QToolButton* rigidbody2DButton = createToolButton(this, physicsWidget, physicsLayout, "Rigidbody2D", GameEngine::GameEngineComponentType::Rigidbody2DComponent);
    this->trie->insert("rigidbody2D", physicsButton);
    
    QToolButton* BoxCollider2DNutton = createToolButton(this, physicsWidget, physicsLayout, "BoxCollider2D", GameEngine::GameEngineComponentType::BoxCollider2DComponent);
    this->trie->insert("BoxCollider2D", physicsButton);

    return physicsWidget;
}

void ComponentBrowserWidget::hideAllComponentBrowser()
{
    for (int i = 0; i < this->browserLayout->count(); ++i)
    {
        this->browserLayout->itemAt(i)->widget()->hide();
    }
}

void ComponentBrowserWidget::onToolButtonClick()
{
    emit this->onAddComponentSignal();
}

void ComponentBrowserWidget::filterComponentBrowser()
{
    this->hideAllComponentBrowser();
    std::vector<QToolButton*> buttons = this->trie->getAllStartWith(this->searchBar->text().toStdString());
    for (QToolButton* button: buttons)
    {
        button->show();
    }
    if (buttons.empty())
    {
        //當找不到button時觸發
        //解決QMenu不更新size的問題
        this->browserWrap->adjustSize();
        this->componentBrowserStackedWidget->adjustSize();
        this->adjustSize();
    }
    QResizeEvent re(QSize(), this->menuPtr->size());
    qApp->sendEvent(this->menuPtr, &re);
    this->menuPtr->adjustSize();
}

//ComponentBrowserButton
ComponentBrowserButton::ComponentBrowserButton(QWidget *parent)
    : QToolButton(parent)
    , popupWidget(new QWidgetAction(this))
    , menu(new QMenu(this))
{
    this->setPopupMode(QToolButton::InstantPopup);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    this->setObjectName("toolButton_addComponent");
    this->setText("Add component");

    this->componentBrowserWidget = new ComponentBrowserWidget(this->menu);
    this->popupWidget->setDefaultWidget(componentBrowserWidget);
    this->menu->addAction(this->popupWidget);
    this->setMenu(this->menu);

    connect(this->menu, &QMenu::aboutToShow, [this](){
        this->menu->setMinimumWidth(this->width());

        if (this->componentBrowserWidget->getCurrentPageIndex() != 0)
            this->componentBrowserWidget->swithToHomePage();

        QResizeEvent re(QSize(), this->menu->size());
        qApp->sendEvent(this->menu, &re);
        this->menu->adjustSize();
    });
}

