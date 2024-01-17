#ifndef WINDOWS_API_H
#define WINDOWS_API_H

#include "Core/Platform.h"

namespace GameEngineEditor
{
    #if USE_WINDOWS
    class WindowsApi
    {
    public:
        static const char* openProjectFile();
    };
    #endif
}

#endif