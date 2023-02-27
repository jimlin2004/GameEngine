#ifndef ASSET_FILE_WIDGET_H
#define ASSET_FILE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>

class AssetFileWidget: public QWidget
{
    Q_OBJECT
public:
    AssetFileWidget(QWidget *parent = nullptr);
    AssetFileWidget(const QString& assetName, QWidget *parent = nullptr);
    ~AssetFileWidget();
protected:
    void paintEvent(QPaintEvent* event);
private:
    QWidget* widget_icon;
    QLabel* label_assetName;
};

#endif