#ifndef EDITOR_COLOR_H
#define EDITOR_COLOR_H

#include "imgui.h"

#define COLOR_TO_IMVEC4(color) (ImGui::ColorConvertU32ToFloat4(color))

namespace GameEngineEditor
{
    constexpr ImU32 defaultHovered           = IM_COL32(100, 100, 100, 255);
    constexpr ImU32 defaultActive            = IM_COL32(70, 70, 70, 255);
    //Title
    constexpr ImU32 TitleBarColor            = IM_COL32(17, 17, 17, 255);
    constexpr ImU32 TitleBarActiveColor      = IM_COL32(40, 40, 40, 255);
    //window
    constexpr ImU32 WindowColor              = IM_COL32(70, 70, 70, 255);
    //tab
    constexpr ImU32 TabActiveColor           = defaultActive;
    constexpr ImU32 TabColor                 = IM_COL32(25, 25, 25, 255);
    constexpr ImU32 TabUnfocusedColor        = IM_COL32(17, 17, 17, 255);
    constexpr ImU32 TabUnfocusedActiveColor  = defaultActive;
    constexpr ImU32 TabHoveredColor          = defaultHovered;
    //TreeNode
    constexpr ImU32 TreeNodeColor            = IM_COL32(70, 70, 70, 255);
    constexpr ImU32 TreeNodeHoveredColor     = defaultHovered;
    constexpr ImU32 TreeNodeActiveColor      = defaultActive;
    //frame
    constexpr ImU32 FrameColor               = IM_COL32(25, 25, 25, 255);
    //button
    constexpr ImU32 ButtonHoveredColor       = defaultHovered;
    constexpr ImU32 ButtonActiveColor        = defaultActive;
    //header
    constexpr ImU32 HeaderColor              = IM_COL32(40, 40, 40, 255);
    constexpr ImU32 HeaderActiveColor        = defaultActive;
    constexpr ImU32 HeaderHoveredColor       = defaultHovered;

    //Properties
    constexpr ImU32 PropertiesTreeNodeColor  = IM_COL32(25, 25, 25, 255);

    //other
    constexpr ImU32 xAxisColor               = IM_COL32(214, 53, 53, 255);
    constexpr ImU32 yAxisColor               = IM_COL32(53, 214, 85, 255);
    constexpr ImU32 zAxisColor               = IM_COL32(53, 120, 214, 255);
    constexpr ImU32 xAxisHintColor           = IM_COL32(255, 100, 100, 255);
    constexpr ImU32 yAxisHintColor           = IM_COL32(80, 255, 80, 255);
    constexpr ImU32 zAxisHintColor           = IM_COL32(100, 150, 255, 255);
    constexpr ImU32 AddCompnentButtonColor   = IM_COL32(17, 17, 17, 255);
}

#endif