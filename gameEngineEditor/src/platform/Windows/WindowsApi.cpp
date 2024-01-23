#include "Platform/Windows/WindowsApi.h"

#include <cstring>

#include <string>
#if USE_WINDOWS

std::string GameEngineEditor::WindowsApi::openProjectFile(HWND parentID)
{
    CHAR filePathBuffer[512] = {0};
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = parentID;
    ofn.lpstrFilter = "project file(*.gproject)\0*.gproject\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = filePathBuffer;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(filePathBuffer);
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = "Open Project\0";
    ofn.nMaxFileTitle = strlen("Open Project\0");
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if (GetOpenFileNameA(&ofn))
    {
        return ofn.lpstrFile;
    }
    return std::string();
}

#endif