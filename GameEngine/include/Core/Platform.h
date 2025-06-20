#ifndef PLATFORM_H
#define PLATFORM_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define USE_WINDOWS 1
#else
    #define USE_WINDOWS 0
#endif

#endif