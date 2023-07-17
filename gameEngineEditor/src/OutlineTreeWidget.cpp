#include "OutlineTreeWidget.h"

OutlineTreeWidget::OutlineTreeWidget(QWidget* parent)
    : QTreeWidget(parent)
{
}

entt::entity OutlineTreeWidget::getSelectedEntity() const
{
    QList<QTreeWidgetItem*> items = this->selectedItems();
    if (items.size() == 0)
        return entt::null;
    OutlineTreeWidgetItem* outlineItem = dynamic_cast<OutlineTreeWidgetItem*>(items[0]);
    if (outlineItem != nullptr)
        return outlineItem->getEntityID();
    else
        return entt::null; //點到Level的case
}

void OutlineTreeWidget::setSelectedEntity(QTreeWidgetItem* item)
{
    this->setCurrentItem(item);
    this->itemClicked(item, this->currentColumn()); //為了更新detail的資料(mainwindow中有connect)
}
