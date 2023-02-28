#ifndef ASSET_FILE_WIDGET_H
#define ASSET_FILE_WIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <string>

#include "WordWrapLabel.h"
#include "GELib.h"

class AssetFileWidget: public QWidget
{
    Q_OBJECT
public:
    AssetFileWidget(QWidget *parent = nullptr);
    AssetFileWidget(const QString& assetName, QWidget *parent = nullptr);
    AssetFileWidget(const std::string& assetName, QWidget *parent = nullptr);
    ~AssetFileWidget();
protected:
    void paintEvent(QPaintEvent* event);
private:
    QWidget* widget_icon;
    WordWrapLabel* label_assetName;
};

#endif