#ifndef CONSOLEAPI_H
#define CONSOLEAPI_H

#include <stdarg.h>
#include <stdio.h>

namespace GameEngine
{
    class ConsoleApi
    {
    public:
        //將text print 到 console
        static void log(const char* const format, ...);
    };
}

#endif