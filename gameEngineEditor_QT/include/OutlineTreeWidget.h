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
    //僅為mainWindow 的frameless移動時避免搶mouse focus所使用
    void onHitBorderSignal(QPoint);
    //當selected item變Null時觸發
    void onSetSelectedItemToNull();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    virtual void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
private:
    MainWindow* mainWindowPtr;
};

#endif