#include "OutlineTreeWidgetItem.h"

std::map<uint32_t, OutlineTreeWidgetItem*> OutlineTreeWidgetItem::itemsMap = {};

OutlineTreeWidgetItem::OutlineTreeWidgetItem(QTreeWidget *treeview, int type)
    : QTreeWidgetItem(treeview, type)
    , entityID(entt::null)
{
}

OutlineTreeWidgetItem::OutlineTreeWidgetItem(QTreeWidgetItem *parent, int type)
    : QTreeWidgetItem(parent, type)
    , entityID(entt::null)
{
}

void OutlineTreeWidgetItem::setEntityID(entt::entity ID)
{
    this->entityID = ID;
}

void OutlineTreeWidgetItem::click()
{
    qDebug("ID: %u\n", this->entityID);
}

void OutlineTreeWidgetItem::resetItemsVec()
{
    this->itemsMap.clear();
    OutlineTreeWidgetItem* ptr;
    for (int i = 0; i < this->childCount(); ++i)
    {
        ptr = dynamic_cast<OutlineTreeWidgetItem*>(this->child(i));
        assert(ptr != nullptr);
        this->itemsMap.insert({(uint32_t)ptr->getEntityID(), ptr});
    }
}

void OutlineTreeWidgetItem::insertItem(OutlineTreeWidgetItem *item)
{
    OutlineTreeWidgetItem::itemsMap.insert({(uint32_t)item->getEntityID(), item});
}

void OutlineTreeWidgetItem::removeItem(entt::entity entityID)
{
    OutlineTreeWidgetItem::itemsMap.erase((uint32_t)entityID);
}

OutlineTreeWidgetItem *OutlineTreeWidgetItem::getItemByEntityID(entt::entity entityID)
{
    if (entityID == entt::null)
        return nullptr;
    auto it = OutlineTreeWidgetItem::itemsMap.find((uint32_t)entityID);
    return (it == OutlineTreeWidgetItem::itemsMap.end()) ? nullptr : it->second;
}
