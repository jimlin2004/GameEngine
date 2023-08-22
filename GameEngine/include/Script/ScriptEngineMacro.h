#ifndef SCRIPT_ENGINE_MACRO_H
#define SCRIPT_ENGINE_MACRO_H

#ifndef GENGINE_STATIC_LIB
    #ifdef GENGINE_DLL
        #define GENGINE_API __declspec(dllexport)
    #else
        #define GENGINE_API __declspec(dllimport)
    #endif
#else
    #define GENGINE_API
#endif

#endif