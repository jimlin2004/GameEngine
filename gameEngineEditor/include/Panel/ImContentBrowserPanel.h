#ifndef IMCONTENT_BROWSER_PANEL_H
#define IMCONTENT_BROWSER_PANEL_H

#include <filesystem>
#include "imgui.h"
#include "Opengl/Texture.h"

namespace GameEngineEditor
{
    class ImContentBrowserPanel
    {
    public:
        ImContentBrowserPanel();
        void begin();
        void setRootPath(const std::filesystem::path& rootPath);
        void render();
    private:
        GameEngine::Texture* fileIcon;
        GameEngine::Texture* folderIcon;
        std::filesystem::path rootPath;
        std::filesystem::path currentPath;
    };
}

#endif