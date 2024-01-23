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
    };
    
}
#endif

#endif