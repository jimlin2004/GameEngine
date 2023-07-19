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

AssetFileWidget::AssetFileWidget(const QString& assetName, const std::string& absolutePath, QPixmap* sprite, FileType fileType, QWidget *parent)
    : AssetFileWidget(assetName.toStdString(), absolutePath, sprite, fileType, parent)
{
}

AssetFileWidget::AssetFileWidget(const std::string& assetName, const std::string& absolutePath, QPixmap* sprite, FileType fileType, QWidget *parent)
    : QWidget(parent)
    , label_icon(new QLabel())
    , label_assetName(new WordWrapLabel(QString::fromStdString(assetName)))
    , fileType(fileType)
    , absolutePath(absolutePath)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->label_icon->setFixedSize(64, 64);
    this->label_icon->setObjectName("icon");
    QRect cropArea;
    bool isUseIcon = false;
    if (this->fileType == FileType::Fold)
    {
        cropArea = {0, 0, 16, 16};
        isUseIcon = true;
    }
    else if (this->fileType == FileType::File)
    {
        cropArea = {0, 16, 16, 16};
        isUseIcon = true;
    }
    else if (this->fileType == FileType::Texture)
    {
        QPixmap texture = QPixmap(QString::fromStdString(absolutePath));
        texture = texture.scaled(this->label_icon->width(), this->label_icon->height(), Qt::KeepAspectRatio);
        this->label_icon->setPixmap(texture);
    }

    if (isUseIcon)
    {
        QPixmap cropSprite = sprite->copy(cropArea);
        cropSprite = cropSprite.scaled(this->label_icon->width(), this->label_icon->height(), Qt::KeepAspectRatio);
        this->label_icon->setPixmap(cropSprite);
    }
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
    {
        emit click();
        return;
    }
    if (event->button() == Qt::LeftButton)
        this->dragStartPosition = event->pos();
}

void AssetFileWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - this->dragStartPosition).manhattanLength()
        < QApplication::startDragDistance())
        return;
    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;
    mimeData->setData("text/uri-list", QString::fromStdString("file:///" + this->absolutePath).toLocal8Bit());
    drag->setMimeData(mimeData);
    drag->setPixmap(this->label_icon->pixmap());
    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}

const std::string AssetFileWidget::getAssetName()
{
    return this->label_assetName->text().toStdString();
}