#include "AssetFileWidget.h"

AssetFileWidget::AssetFileWidget(QWidget *parent)
    : QWidget(parent)
    , widget_icon(new QWidget())
    , label_assetName(new WordWrapLabel())
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->widget_icon->setFixedSize(64, 64);
    this->widget_icon->setObjectName("icon");
    layout->addStretch(0);
    layout->addWidget(this->widget_icon);
    layout->addWidget(this->label_assetName);
    layout->setContentsMargins(5, 5, 5, 5);
}

AssetFileWidget::AssetFileWidget(const QString& assetName, QWidget *parent)
    : QWidget(parent)
    , widget_icon(new QWidget())
    , label_assetName(new WordWrapLabel(assetName))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->widget_icon->setFixedSize(64, 64);
    this->widget_icon->setObjectName("icon");
    this->label_assetName->setWordWrap(true);
    this->label_assetName->setAlignment(Qt::AlignCenter);
    this->label_assetName->setFixedWidth(64);
    this->label_assetName->wrapText(assetName);
    layout->addStretch(0);
    layout->addWidget(this->widget_icon);
    layout->addWidget(this->label_assetName);
    layout->setContentsMargins(5, 5, 5, 5);
}

AssetFileWidget::AssetFileWidget(const std::string& assetName, QWidget *parent)
    : QWidget(parent)
    , widget_icon(new QWidget())
    , label_assetName(new WordWrapLabel(QString::fromStdString(assetName)))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->widget_icon->setFixedSize(64, 64);
    this->widget_icon->setObjectName("icon");
    this->label_assetName->setWordWrap(true);
    this->label_assetName->setAlignment(Qt::AlignCenter);
    this->label_assetName->setFixedWidth(64);
    this->label_assetName->wrapText(QString::fromStdString(assetName));
    layout->addStretch(0);
    layout->addWidget(this->widget_icon);
    layout->addWidget(this->label_assetName);
    layout->setContentsMargins(5, 5, 5, 5);
}

AssetFileWidget::~AssetFileWidget()
{
    delete this->widget_icon;
    delete this->label_assetName;
}

void AssetFileWidget::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}