#ifndef IMCAMERA_PREVIEW_H
#define IMCAMERA_PREVIEW_H

#include <cstdint>

#include "imgui/imgui.h"

namespace GameEngineEditor
{
    class ImCameraPreview
    {
    public:
        ImCameraPreview();
        void render(void* textureID);
        inline ImVec2 getViewportSize() { return this->viewportSize; }
    private:
        ImVec2 viewportSize;
    };
}

#endif