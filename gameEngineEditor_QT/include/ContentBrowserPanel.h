#ifndef CONTENT_BROWSER_PANEL_H
#define CONTENT_BROWSER_PANEL_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QPixmap>
#include <QPushButton>
#include <filesystem>
#include "flowlayout.h"
#include "AssetFileWidget.h"

class ContentBrowserPanel: public QWidget
{
    Q_OBJECT
public:
    ContentBrowserPanel(QWidget* parent = nullptr);
    void reset();
    void setPath(const std::filesystem::path& path);
    void nextPath(const std::string& next);
private:
    std::filesystem::path projectRootPath;
    std::filesystem::path currentPath;
    QPixmap* spriteSheet;
private slots:
    void clear();
    void onItemClick();
    void back();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent* event);
};

#endif