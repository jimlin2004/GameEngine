#ifndef OUTLINE_TREE_WIDGET_ITEM_H
#define OUTLINE_TREE_WIDGET_ITEM_H

#include <QTreeWidget>
#include <entt.hpp>

class OutlineTreeWidgetItem: public QTreeWidgetItem
{
public:
    OutlineTreeWidgetItem();
    void setEntityID(entt::entity ID);
    inline entt::entity getEntityID() const
    {
        return this->entityID;
    }
    void click();
private:
    entt::entity entityID;
protected:
};

#endif