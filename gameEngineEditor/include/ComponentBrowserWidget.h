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
};

class ComponentBrowserButton: public QToolButton
{
    Q_OBJECT
public:
    explicit ComponentBrowserButton(QWidget *parent = (QWidget *)nullptr);
private:
    QWidgetAction* popupWidget;
    QMenu* menu;
};

class ComponentBrowserWidget: public QWidget
{
    Q_OBJECT
public:
    explicit ComponentBrowserWidget(QMenu* ptr, QWidget* parent = (QWidget*)nullptr);
    static void getComponent();
private:
    ComponentBrowserStackedWidget* componentBrowserStackedWidget;
    ComponentBrowserTrie* trie;
    QWidget* browserWrap;
    QVBoxLayout* browserLayout;
    QLineEdit* searchBar;
    QMenu* menuPtr;

    void setupUI();
    void hideAllComponentBrowser();
private slots:
    void filterComponentBrowser();
};



#endif