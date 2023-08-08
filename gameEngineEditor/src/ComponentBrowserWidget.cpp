#include "ComponentBrowserWidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <memory.h>
#include "Core/Assert.h"

bool ComponentBrowserTriePair::operator<(const ComponentBrowserTriePair &other) const
{
    return (this->data < other.data);
}

ComponentBrowserTrieNode::ComponentBrowserTrieNode()
    : isWord(false)
    , hasNext(false)
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

void ComponentBrowserTrieNode::insert(const std::string& str)
{
    ComponentBrowserTrieNode* current = this;
    int index = 0;
    int target;
    char c;
    for (int strIndex = 0; strIndex < str.size(); ++i)
    {
        //只存小寫字母或一些_、&、!等符號
        c = str[i];
        target = tolower(c) - 'a';
        index = current->binarySearch(target);        
        if (index == -1)
        {
            //代表需要擴充空間
            ComponentBrowserTriePair newPair = {c, new ComponentBrowserTrieNode()};
            ++this->size;
            this->nexts = realloc(this->nextsm, sizeof(ComponentBrowserTriePair) * this->size);
            GAME_ENGINE_ASSERT(this->nexts == NULL, "Can't realloc more memory");

            auto it = std::lower_bound(this->nexts, this->nexts + this->size, newPair);
            for (int i = this->size - 1; i > it - this->nexts; --i)
                this->nexts[i] = this->nexts[i - 1];
            this->nexts[it - this->nexts] = newPair;
            current = newPair;
        }
        else
        {
            current = this->nexts[index];
        }
        if (i == this->size - 1)
            current->isWord = true;
    }
    
}

//ComponentBrowserTrie
ComponentBrowserTrie::ComponentBrowserTrie()
    : root(new ComponentBrowserTrieNode())
{
}

void ComponentBrowserTrie::insert(const std::string& str)
{

}

std::vector<std::string> ComponentBrowserTrie::getAllStartWith(const std::string& prefix) const
{
    return std::vector<std::string>();
}

//ComponentBrowserStackedWidget
ComponentBrowserStackedWidget::ComponentBrowserStackedWidget(QWidget* parent)
    : QStackedWidget(parent)
{
}

//ComponentBrowserWidget
ComponentBrowserWidget::ComponentBrowserWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setupUI();
}

void ComponentBrowserWidget::setupUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    this->setLayout(layout);

    //search bar
    QLineEdit* searchBar = new QLineEdit(this);
    searchBar->addAction(QIcon(":/icon/icon/search.png"), QLineEdit::LeadingPosition);
    searchBar->setClearButtonEnabled(true);
    searchBar->setPlaceholderText("Search...");
    searchBar->setObjectName("searchBar");
    layout->addWidget(searchBar);

    // componentBrowser
    this->componentBrowserStackedWidget = new ComponentBrowserStackedWidget(this);

    QScrollArea* scrollarea = new QScrollArea(this->componentBrowserStackedWidget);
    QWidget* browserWrap = new QWidget(scrollarea);
    scrollarea->setWidget(browserWrap);

    QVBoxLayout* browserLayout = new QVBoxLayout(browserWrap);
    browserLayout->setContentsMargins(0, 0, 0, 0);
    browserLayout->setSpacing(0);
    browserWrap->setLayout(browserLayout);

    QToolButton* transformButton = new QToolButton(browserWrap);
    transformButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    transformButton->setText("Transform");
    browserLayout->addWidget(transformButton);

    this->componentBrowserStackedWidget->addWidget(browserWrap);

    layout->addWidget(this->componentBrowserStackedWidget);
}

void ComponentBrowserWidget::getComponent()
{
    
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

    ComponentBrowserWidget* componentBrowserWidget = new ComponentBrowserWidget();
    this->popupWidget->setDefaultWidget(componentBrowserWidget);
    this->menu->addAction(this->popupWidget);
    this->setMenu(this->menu);
}


