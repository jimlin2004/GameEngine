#include "OutlineTreeWidgetItem.h"

OutlineTreeWidgetItem::OutlineTreeWidgetItem()
    : QTreeWidgetItem()
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
