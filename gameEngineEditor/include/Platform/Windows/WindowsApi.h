#ifndef WINDOWS_API_H
#define WINDOWS_API_H

#include "Core/Platform.h"

#include <string>
#if USE_WINDOWS
#include "windows.h"

namespace GameEngineEditor
{
    class WindowsApi
    {
    public:
        static std::string openProjectFile(HWND parentID = NULL);
        static std::string openFile(HWND parentID = NULL, const char* filter = nullptr);
    };
}
#endif

#endif