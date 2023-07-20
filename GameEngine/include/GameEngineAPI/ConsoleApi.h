#ifndef CONSOLEAPI_H
#define CONSOLEAPI_H

#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include "Core/UUID.h"

namespace GameEngine
{
    struct MousePosition;
    
    using Logger = std::ostream;

    class ConsoleApi
    {
    public:
        //將text print 到 console
        static void log(const char* const format, ...);
        static inline constexpr Logger& log()
        {
            return std::cout;
        }
    };

    Logger& operator << (Logger& logger, const MousePosition& mousePosition);
    Logger& operator << (Logger& logger, const UUID& uuid);
}

#endif