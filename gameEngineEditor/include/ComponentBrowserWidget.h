#ifndef COMPONENT_BROWSER_WIDGET
#define COMPONENT_BROWSER_WIDGET

#include <QWidget>
#include <QWidgetAction>
#include <QToolButton>
#include <QMenu>
#include <QStackedWidget>
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

private:
    bool isWord;
    bool hasNext;
    uint32_t size;
    ComponentBrowserTriePair* nexts; //child array

    int binarySearch(char target);
    void insert(const std::string& str);
    friend class ComponentBrowserTrie;
};

//用於加速component browser的search功能
class ComponentBrowserTrie
{
public:
    explicit ComponentBrowserTrie();

    void insert(const std::string& str);
    std::vector<std::string> getAllStartWith(const std::string& prefix) const;
private:
    ComponentBrowserTrieNode* root;
};

class ComponentBrowserStackedWidget: public QStackedWidget
{
    Q_OBJECT
public:
    explicit ComponentBrowserStackedWidget(QWidget* parent = (QWidget*)nullptr);
};

class ComponentBrowserWidget: public QWidget
{
    Q_OBJECT
public:
    explicit ComponentBrowserWidget(QWidget* parent = (QWidget*)nullptr);
    static void getComponent();
private:
    ComponentBrowserStackedWidget* componentBrowserStackedWidget;

    void setupUI();
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

#endif