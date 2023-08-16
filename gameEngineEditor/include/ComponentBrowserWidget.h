#ifndef COMPONENT_BROWSER_WIDGET
#define COMPONENT_BROWSER_WIDGET

#include <QWidget>
#include <QWidgetAction>
#include <QToolButton>
#include <QMenu>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <vector>
#include <stdint.h>

#include "Component/Component.h"
#include "MainWindowExportData.h"

class ComponentBrowserTrieNode;

struct ComponentBrowserTriePair
{
    char data;
    ComponentBrowserTrieNode* trieNodePtr;

    bool operator < (const ComponentBrowserTriePair& other) const;
};

class ComponentBrowserTrieNode
{
public:
    explicit ComponentBrowserTrieNode();

    void insert(const std::string& str, QToolButton* targetPtr);
    bool queryNext(char target);
private:
    uint32_t size;
    QToolButton* buttonPtr;
    ComponentBrowserTriePair* nexts; //child array

    int binarySearch(char target);
    void dfs(std::vector<QToolButton*>& res);
    bool isWord() const;
    friend class ComponentBrowserTrie;
};

//用於加速component browser的search功能
class ComponentBrowserTrie
{
public:
    explicit ComponentBrowserTrie();

    void insert(const std::string& str, QToolButton* targetPtr);
    std::vector<QToolButton*> getAllStartWith(const std::string& prefix) const;
private:
    ComponentBrowserTrieNode* root;
};

class ComponentBrowserStackedWidget: public QStackedWidget
{
    Q_OBJECT
public:
    explicit ComponentBrowserStackedWidget(QWidget* parent = (QWidget*)nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    virtual void showEvent(QShowEvent* event);
};

class ComponentBrowserWidget: public QWidget
{
    Q_OBJECT
public:
    explicit ComponentBrowserWidget(QMenu* ptr, QWidget* parent = (QWidget*)nullptr);
    void bindExportDataPtr(GameEngineEditor::ExportData* ptr);
    void setSelectedComponentType(GameEngine::GameEngineComponentType type);
    void swithToHomePage();
    inline int getCurrentPageIndex() const
    {
        return this->componentBrowserStackedWidget->currentIndex();
    }
    inline GameEngine::GameEngineComponentType getSelectedComponentType() const
    {
        return this->selectedComponentType;
    }
signals:
    //內部使用
    void onAddComponentSignal();
    
    //當呼叫entityAddComponent時觸發
    void onAddedComponent();
public slots:
    void onToolButtonClick();
private:
    GameEngineEditor::ExportData* exportDataPtr;
    ComponentBrowserStackedWidget* componentBrowserStackedWidget;
    ComponentBrowserTrie* trie;
    QWidget* browserWrap;
    QVBoxLayout* browserLayout;
    QLineEdit* searchBar;
    QMenu* menuPtr;
    GameEngine::GameEngineComponentType selectedComponentType;

    void setupUI();
    QWidget* setupPhysicsWidget();
    void hideAllComponentBrowser();
    void entityAddComponent(entt::entity &entityID, GameEngine::GameEngineComponentType type);
private slots:
    void filterComponentBrowser();
};

class ComponentBrowserButton: public QToolButton
{
    Q_OBJECT
public:
    explicit ComponentBrowserButton(QWidget *parent = (QWidget *)nullptr);

    inline ComponentBrowserWidget* getPopupWidget() const
    {
        return this->componentBrowserWidget;
    }
private:
    QWidgetAction* popupWidget;
    ComponentBrowserWidget* componentBrowserWidget;
    QMenu* menu;
};
#endif