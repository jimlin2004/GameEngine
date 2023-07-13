#ifndef OUTLINE_TREE_WIDGET_H
#define OUTLINE_TREE_WIDGET_H

#include <QTreeWidget>
#include "OutlineTreeWidgetItem.h"
#include "entt.hpp"

class OutlineTreeWidget: public QTreeWidget
{
    Q_OBJECT
public:
    OutlineTreeWidget(QWidget* parent = nullptr);

    entt::entity getSelectedEntity() const;

};

#endif