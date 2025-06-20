#include "Panel/ImContentBrowserPanel.h"

#include "EditorColor.h"
#include <filesystem>

GameEngineEditor::ImContentBrowserPanel::ImContentBrowserPanel()
{
}

void GameEngineEditor::ImContentBrowserPanel::begin()
{
    std::filesystem::path exePath = std::filesystem::current_path();
    std::filesystem::path assetsPath = exePath / "assets";
    this->fileIcon = new GameEngine::Texture();
    this->folderIcon = new GameEngine::Texture();
    std::string fileIconPath = (assetsPath / "texture" / "file.png").u8string();
    this->fileIcon->load(fileIconPath.c_str(), GL_NEAREST);
    std::string folderIconPath = (assetsPath / "texture" / "folder.png").u8string();
    this->folderIcon->load(folderIconPath.c_str(), GL_NEAREST);
}

void GameEngineEditor::ImContentBrowserPanel::setRootPath(const std::filesystem::path &rootPath)
{
    this->rootPath = rootPath / "assets";
    this->currentPath = this->rootPath;
}

void GameEngineEditor::ImContentBrowserPanel::render()
{
    ImGui::Begin("Content Browser");
        float panelWidth = ImGui::GetContentRegionAvail().x;
        static const float iconSize = 64;
        static const float padding = 16;
        const float cellSize = iconSize + padding;
        int columnsNum = (int)(panelWidth / cellSize);
        if (columnsNum < 1)
            columnsNum = 1;
        if (!this->rootPath.empty())
        {
            if (this->currentPath != this->rootPath)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::defaultHovered);
                if (ImGui::Button(".."))
                {
                    this->currentPath = this->currentPath.parent_path();
                }
                ImGui::PopStyleColor(1);
            }
            ImGui::Columns(columnsNum, NULL, false);
            for (auto item: std::filesystem::directory_iterator(this->currentPath))
            {
                std::string filename = item.path().filename().u8string();
                GameEngine::Texture* icon;
                bool isDirectory = std::filesystem::is_directory(item.path());
                if (isDirectory)
                    icon = this->folderIcon;
                else
                    icon = this->fileIcon;
                ImGui::PushID(filename.c_str());
                ImGui::PushStyleColor(ImGuiCol_Button, GameEngineEditor::defaultHovered);
                if (ImGui::ImageButton(reinterpret_cast<void*>(icon->getTextureID()), {iconSize, iconSize}, {0, 1}, {1, 0}))
                {
                    if (isDirectory)
                        this->currentPath /= filename;
                }
                if (!isDirectory)
                {
                    if (ImGui::BeginDragDropSource())
                    {
                        std::filesystem::path pathCopy(item.path());
                        const wchar_t* itemPath = pathCopy.c_str();
                        ImGui::SetDragDropPayload("ContentBrowserItem", (const void*)(itemPath), (wcslen(itemPath) + 1) * (sizeof(wchar_t)));
                        ImGui::EndDragDropSource();
                    }
                }
                ImGui::TextWrapped(filename.c_str());
                ImGui::PopStyleColor(1);
                ImGui::PopID();
                ImGui::NextColumn();
            }
        }
        ImGui::Columns(1);
    ImGui::End();
}
