#ifndef ASSET_FILE_WIDGET_H
#define ASSET_FILE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <string>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

#include "WordWrapLabel.h"
#include "Core/GELib.h"

enum FileType
{
    Fold,
    File,
    Texture
};

class AssetFileWidget: public QWidget
{
    Q_OBJECT
public:
    AssetFileWidget(QWidget *parent = nullptr);
    AssetFileWidget(const QString& assetName, const std::string& absolutePath, QPixmap* sprite, FileType fileType, QWidget *parent = nullptr);
    AssetFileWidget(const std::string& assetName, const std::string& absolutePath, QPixmap* sprite, FileType fileType, QWidget *parent = nullptr);
    virtual ~AssetFileWidget();

    const std::string getAssetName();

signals:
    void click();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    QLabel* label_icon;
    WordWrapLabel* label_assetName;
    std::string absolutePath;
    FileType fileType;
    QPoint dragStartPosition;
};

#endif