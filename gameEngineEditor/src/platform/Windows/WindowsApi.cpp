#include "Platform/Windows/WindowsApi.h"

#include "string.h"

#if USE_WINDOWS
    #include "windows.h"

const char *GameEngineEditor::WindowsApi::openProjectFile()
{
    LPSTR filePathBuffer = new char[512];
    OPENFILENAME open = {0};
    ZeroMemory(&open, sizeof(OPENFILENAME));
    open.lStructSize = sizeof(OPENFILENAME);
    open.hwndOwner = NULL;
    open.lpstrFilter = "project file\0*.gproject\0";
    open.nFilterIndex = 1;
    open.lpstrFile = filePathBuffer;
    open.lpstrFile[0] = '\0';
    open.nMaxFile = 512;
    open.lpstrInitialDir = NULL;
    open.lpstrTitle = "Open Project\0";
    open.nMaxFileTitle = strlen("Open Project\0");
    open.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if (GetOpenFileName(&open))
    {
        return open.lpstrFile;
    }
    return nullptr;
}

#endif