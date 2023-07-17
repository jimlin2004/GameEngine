#include "OutlineTreeWidgetItem.h"

#include <algorithm>

std::vector<OutlineTreeWidgetItem*> OutlineTreeWidgetItem::itemsVec = {};

OutlineTreeWidgetItem::OutlineTreeWidgetItem(QTreeWidget *treeview, int type)
    : QTreeWidgetItem(treeview, type)
{
}

OutlineTreeWidgetItem::OutlineTreeWidgetItem(QTreeWidgetItem *parent, int type)
    : QTreeWidgetItem(parent, type)
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

static bool cmp(OutlineTreeWidgetItem* a, OutlineTreeWidgetItem* b)
{
    return (uint32_t)(*a).getEntityID() < (uint32_t)(*b).getEntityID();
}

void OutlineTreeWidgetItem::resetItemsVec()
{
    this->itemsVec.clear();
    OutlineTreeWidgetItem* ptr;
    for (int i = 0; i < this->childCount(); ++i)
    {
        ptr = dynamic_cast<OutlineTreeWidgetItem*>(this->child(i));
        assert(ptr != nullptr);
        this->itemsVec.emplace_back(ptr);
    }
    std::sort(this->itemsVec.begin(), this->itemsVec.end(), cmp);
}

OutlineTreeWidgetItem *OutlineTreeWidgetItem::getItemByEntityID(entt::entity entityID) const
{
    //binary search
    int left = 0, right = this->itemsVec.size() - 1;
    int mid;
    while (left <= right)
    {
        mid = left + ((right - left) >> 1);
        if (this->itemsVec[mid]->getEntityID() > entityID) 
            right = mid - 1;
        else if (this->itemsVec[mid]->getEntityID() < entityID)
            left = mid + 1;
        else 
            return this->itemsVec[mid];
    }
    return nullptr;
}
