#ifndef OUTLINE_TREE_WIDGET_ITEM_H
#define OUTLINE_TREE_WIDGET_ITEM_H

#include <QTreeWidget>

class OutlineTreeWidgetItem: public QTreeWidgetItem
{
public:
    OutlineTreeWidgetItem();
    void setEntityID(std::uint32_t ID);
    inline std::uint32_t getEntityID() const
    {
        return this->entityID;
    }
private:
    std::uint32_t entityID;
};

#endif