#include "ContentBrowserPanel.h"

ContentBrowserPanel::ContentBrowserPanel(QWidget *parent)
    : QWidget(parent)
    , spriteSheet(new QPixmap("./assets/texture/filesystem.png"))
{
    this->setLayout(new FlowLayout());
    this->setAcceptDrops(true);
}

void ContentBrowserPanel::reset()
{
    this->clear();

    if (!std::filesystem::exists(this->currentPath))
        return;

    //添加上一頁的按鍵
    if (this->currentPath != this->projectRootPath)
    {
        QPushButton* backButton = new QPushButton(this);
        backButton->setText("..");
        backButton->setFixedSize(64, 64);
        this->layout()->addWidget(backButton);
        connect(backButton, &QPushButton::clicked, this, &ContentBrowserPanel::back);
    }

    std::filesystem::directory_entry entry(this->currentPath);
    std::filesystem::directory_iterator fileList(this->currentPath);
    std::string filename;
    AssetFileWidget* assetFileWidget;
    for (auto& file: fileList)
    {
        filename = file.path().filename().u8string();
        if (std::filesystem::is_directory(file.path()))
            assetFileWidget = new AssetFileWidget(filename, file.path().u8string(), this->spriteSheet, FileType::Fold);
        else
            assetFileWidget = new AssetFileWidget(filename, file.path().u8string(), this->spriteSheet, FileType::File);
        this->layout()->addWidget(assetFileWidget);
        connect(assetFileWidget, &AssetFileWidget::click, this, &ContentBrowserPanel::onItemClick);
    }
}

void ContentBrowserPanel::nextPath(const std::string& next)
{
    this->currentPath /= next;
    this->reset();
}

void ContentBrowserPanel::back()
{
    if (this->currentPath != this->projectRootPath)
        this->currentPath = this->currentPath.parent_path();
    this->reset();
}

void ContentBrowserPanel::setPath(const std::filesystem::path& path)
{
    this->currentPath = path;
    this->projectRootPath = path;
}

void ContentBrowserPanel::clear()
{
    QLayoutItem* _item;
    QWidget* _widget;
    QLayout* flowLayout = this->layout();
    while (_item = flowLayout->takeAt(0))
    {
        _widget = _item->widget();
        delete _widget;
        delete _item;
    }
}

void ContentBrowserPanel::onItemClick()
{
    AssetFileWidget* assetFileWidgget = qobject_cast<AssetFileWidget*>(QObject::sender());
    this->currentPath /= assetFileWidgget->getAssetName();
    this->reset();
}

void ContentBrowserPanel::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

void ContentBrowserPanel::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();
    qDebug() << mimeData->formats() << '\n';
    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();
        for (int i = 0; i < urlList.size(); ++i)
        {
            qDebug() << urlList.at(i) << '\n';
        }
    }
}
