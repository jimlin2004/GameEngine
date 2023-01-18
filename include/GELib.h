#ifndef GELIB_H
#define GELIB_H

/*
    author: JimLin
    作用: 此header為GameEngine所需的常用函示集合的lib
*/

namespace GameEngine
{
    template<class T>
    T max(T a, T b)
    {
        return (a < b) ? b : a;
    }
    template<class T, class... Args>
    T max(T a, Args... args)
    {
        return max(a, max(args...));
    }
}

#endif