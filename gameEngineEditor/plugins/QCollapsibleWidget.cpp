#include "QCollapsibleWidget.h"

QCollapsibleWidget::QCollapsibleWidget(QWidget *parent)
    : QWidget(parent)
    , verticalLayout(new QVBoxLayout(this))
    , contentWidget(nullptr)
    , pushButton(new QPushButton())
    , isContentClose(false)
    , needToInsertPushButton(true)
{
    this->verticalLayout->setAlignment(Qt::AlignTop);
    this->verticalLayout->setObjectName("verticalLayout");
    //必須使用這個，不能在constuctor中呼叫，猜測是因為QPushbutton的constructor呼叫QWidget
    //否則childEvent會出錯
    this->pushButton->setParent(this);
    this->pushButton->setObjectName("pushButton");
    if (this->needToInsertPushButton)
        this->verticalLayout->addWidget(this->pushButton);
    this->verticalLayout->setContentsMargins(0, 0, 0, 0);
    this->verticalLayout->setSpacing(0);

    connect(this->pushButton, &QPushButton::clicked, this, &QCollapsibleWidget::changeContentState);
}

QString QCollapsibleWidget::getTitle() const
{
    return this->pushButton->text();
}

void QCollapsibleWidget::setTitle(QString title)
{
    this->pushButton->setText(title);
}

void QCollapsibleWidget::setLayout(QLayout* layout)
{
    this->contentWidget->setLayout(layout);
}

void QCollapsibleWidget::childEvent(QChildEvent *event)
{
    if (event->type() == QChildEvent::ChildAdded)
    {
        if (event->child()->isWidgetType())
        {
            QWidget* widget = qobject_cast<QWidget*>(event->child());
            if (qobject_cast<QPushButton*>(widget) != nullptr)//如果不用designer，會抓到pushbutton
            {
                //此時contentWidget需要在此加入
                this->verticalLayout->addWidget(widget);
                this->contentWidget = new QWidget(this);
                this->needToInsertPushButton = false;
                return;
            }
            if (widget != nullptr)
            {
                this->contentWidget = widget;
                this->contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                this->verticalLayout->addWidget(this->contentWidget);
            }
            else
            {
                this->setObjectName("Add child error!!");
                this->contentWidget = nullptr;
            }
        }
    }
}

void QCollapsibleWidget::changeContentState()
{
    if (this->isContentClose)
    {
        this->contentWidget->show();
        this->isContentClose = false;
    }
    else
    {
        this->contentWidget->hide();
        this->isContentClose = true;
    }
}

QString QCollapsibleWidget::getPushButtonStyle() const
{
    return this->pushButton->styleSheet();
}
void QCollapsibleWidget::setPushButtonStyle(QString styleSheet)
{
    this->pushButton->setStyleSheet(styleSheet);
}
