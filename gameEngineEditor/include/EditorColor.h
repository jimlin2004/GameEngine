#ifndef EDITOR_COLOR_H
#define EDITOR_COLOR_H

#include <cstdint>

//rgba must be uint32_t                   A                                B                               G                               R
#define RGBA_TO_ABGR(rgba) (((0x000000ffU & (rgba)) << 24) | ((0x0000ff00U & (rgba)) << 8) | ((0x00ff0000U & (rgba)) >> 8) | ((0xff000000U & (rgba)) >> 24))

namespace GameEngineEditor
{
    //ImGui中用ABGR
    constexpr uint32_t defaultBgBlack = RGBA_TO_ABGR(0x272829FFU);
    constexpr uint32_t defaultBgGrey  = RGBA_TO_ABGR(0x2B2B2BFFU);
    constexpr uint32_t lightRed       = RGBA_TO_ABGR(0xFF6868FFU);
}

#endif