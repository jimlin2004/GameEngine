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

#include "WordWrapLabel.h"
#include "GELib.h"

enum FileType
{
    Fold,
    File
};

class AssetFileWidget: public QWidget
{
    Q_OBJECT
public:
    AssetFileWidget(QWidget *parent = nullptr);
    AssetFileWidget(const QString& assetName, QPixmap* sprite, FileType fileType, QWidget *parent = nullptr);
    AssetFileWidget(const std::string& assetName, QPixmap* sprite, FileType fileType, QWidget *parent = nullptr);
    ~AssetFileWidget();

    const std::string getAssetName();

signals:
    void click();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
private:
    QLabel* label_icon;
    WordWrapLabel* label_assetName;
    FileType fileType;
};

#endif