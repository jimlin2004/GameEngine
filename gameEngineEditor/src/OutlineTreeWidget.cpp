#include "OutlineTreeWidget.h"

OutlineTreeWidget::OutlineTreeWidget(QWidget* parent)
    : QTreeWidget(parent)
{
}

entt::entity OutlineTreeWidget::getSelectedEntity() const
{
    QList<QTreeWidgetItem *> items = this->selectedItems();
    if (items.size() == 0)
        return entt::null;
    OutlineTreeWidgetItem* outlineItem = dynamic_cast<OutlineTreeWidgetItem*>(items[0]);
    if (outlineItem != nullptr)
        return outlineItem->getEntityID();
    else
        throw std::runtime_error("Outline item is nullptr");
}
