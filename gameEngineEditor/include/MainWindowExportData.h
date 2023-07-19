#ifndef MAIN_WINDOW_EXPORT_DATA_H
#define MAIN_WINDOW_EXPORT_DATA_H

#include "OutlineTreeWidget.h"
#include "OutlineTreeWidgetItem.h"
#include "entt.hpp"

namespace GameEngineEditor
{
    struct ExportData
    {
        OutlineTreeWidget* outlineTreeWidget   = nullptr;
        OutlineTreeWidgetItem* actorCollection = nullptr;
        entt::entity needToInsertOutlineTreeWidget = entt::null;
    };
}

#endif