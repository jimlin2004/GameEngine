#include "AssetFileWidget.h"

AssetFileWidget::AssetFileWidget(QWidget *parent)
    : QWidget(parent)
    , widget_icon(new QWidget())
    , label_assetName(new QLabel())
{

}

AssetFileWidget::AssetFileWidget(const QString& assetName, QWidget *parent)
    : QWidget(parent)
    , widget_icon(new QWidget())
    , label_assetName(new QLabel(assetName))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->widget_icon->resize(50, 50);
    this->widget_icon->setObjectName("icon");
    QFont font = this->label_assetName->font();
    font.setPointSize(9);
    this->label_assetName->setFont(font);
    // layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(this->widget_icon);
    layout->addWidget(this->label_assetName);
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