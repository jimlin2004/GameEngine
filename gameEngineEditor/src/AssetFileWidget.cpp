#include "AssetFileWidget.h"

AssetFileWidget::AssetFileWidget(QWidget *parent)
    : QWidget(parent)
    , label_icon(new QLabel())
    , label_assetName(new WordWrapLabel())
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->label_icon->setFixedSize(64, 64);
    this->label_icon->setObjectName("icon");
    layout->addStretch(0);
    layout->addWidget(this->label_icon);
    layout->addWidget(this->label_assetName);
    layout->setContentsMargins(5, 5, 5, 5);
    this->setCursor(Qt::PointingHandCursor);
}

AssetFileWidget::AssetFileWidget(const QString& assetName, QPixmap* sprite, FileType fileType, QWidget *parent)
    : QWidget(parent)
    , label_icon(new QLabel())
    , label_assetName(new WordWrapLabel(assetName))
    , fileType(fileType)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->label_icon->setFixedSize(64, 64);
    this->label_icon->setObjectName("icon");
    QRect cropArea;
    if (this->fileType == FileType::Fold)
        cropArea = {0, 0, 16, 16};
    else
        cropArea = {0, 16, 16, 16};
    QPixmap cropSprite = sprite->copy(cropArea);
    cropSprite.scaled(this->label_icon->width(), this->label_icon->height(), Qt::KeepAspectRatio);
    this->label_icon->setPixmap(cropSprite);
    this->label_assetName->setWordWrap(true);
    this->label_assetName->setAlignment(Qt::AlignCenter);
    this->label_assetName->setFixedWidth(64);
    this->label_assetName->wrapText(assetName);
    layout->addStretch(0);
    layout->addWidget(this->label_icon);
    layout->addWidget(this->label_assetName);
    layout->setContentsMargins(5, 5, 5, 5);
    this->setCursor(Qt::PointingHandCursor);
}

AssetFileWidget::AssetFileWidget(const std::string& assetName, QPixmap* sprite, FileType fileType, QWidget *parent)
    : QWidget(parent)
    , label_icon(new QLabel())
    , label_assetName(new WordWrapLabel(QString::fromStdString(assetName)))
    , fileType(fileType)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->label_icon->setFixedSize(64, 64);
    this->label_icon->setObjectName("icon");
    QRect cropArea;
    if (this->fileType == FileType::Fold)
        cropArea = {0, 0, 16, 16};
    else
        cropArea = {0, 16, 16, 16};
    QPixmap cropSprite = sprite->copy(cropArea);
    cropSprite = cropSprite.scaled(this->label_icon->width(), this->label_icon->height(), Qt::KeepAspectRatio);
    this->label_icon->setPixmap(cropSprite);
    this->label_assetName->setWordWrap(true);
    this->label_assetName->setAlignment(Qt::AlignCenter);
    this->label_assetName->setFixedWidth(64);
    this->label_assetName->wrapText(QString::fromStdString(assetName));
    layout->addStretch(0);
    layout->addWidget(this->label_icon);
    layout->addWidget(this->label_assetName);
    layout->setContentsMargins(5, 5, 5, 5);
    this->setCursor(Qt::PointingHandCursor);
}

AssetFileWidget::~AssetFileWidget()
{
    delete this->label_icon;
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

void AssetFileWidget::mousePressEvent(QMouseEvent *event)
{
    if (this->fileType == FileType::Fold)
        emit click();
}

const std::string AssetFileWidget::getAssetName()
{
    return this->label_assetName->text().toStdString();
}