#ifndef OUTLINE_TREE_WIDGET_H
#define OUTLINE_TREE_WIDGET_H

#include <QTreeWidget>
#include <QMouseEvent>
#include "OutlineTreeWidgetItem.h"
#include "entt.hpp"

class MainWindow;

class OutlineTreeWidget: public QTreeWidget
{
    Q_OBJECT
public:
    OutlineTreeWidget(QWidget* parent = nullptr);

    entt::entity getSelectedEntity() const;
    void setSelectedEntity(QTreeWidgetItem* item);
    void bindMainWindowPtr(MainWindow* ptr);
signals:
    void onHitBorderSignal(QPoint);
protected:
    void mousePressEvent(QMouseEvent *event) override;
private:
    MainWindow* mainWindowPtr;
};

#endif