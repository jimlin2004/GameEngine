#ifndef OUTLINE_TREE_WIDGET_ITEM_H
#define OUTLINE_TREE_WIDGET_ITEM_H

#include <map>
#include <QChildEvent>
#include <QTreeWidget>
#include <entt.hpp>

class OutlineTreeWidgetItem: public QTreeWidgetItem
{
public:
    OutlineTreeWidgetItem(QTreeWidget *treeview, int type = 0);
    OutlineTreeWidgetItem(QTreeWidgetItem *parent, int type = 0);
    void setEntityID(entt::entity ID);
    inline entt::entity getEntityID() const
    {
        return this->entityID;
    }
    void click();
    void resetItemsVec();
    void insertItem(OutlineTreeWidgetItem* item);
    OutlineTreeWidgetItem* getItemByEntityID(entt::entity entityID) const;
private:
    entt::entity entityID;
    static std::map<uint32_t, OutlineTreeWidgetItem*> itemsMap;
};

#endif