#include "OutlineTreeWidgetItem.h"

OutlineTreeWidgetItem::OutlineTreeWidgetItem()
    : QTreeWidgetItem()
{
}

void OutlineTreeWidgetItem::setEntityID(std::uint32_t ID)
{
    this->entityID = ID;
}