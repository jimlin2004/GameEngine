#ifndef GELIB_H
#define GELIB_H

#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "glm/glm.hpp"

/*
    author: JimLin
    作用: 此header為GameEngine所需常用函式的lib
*/

//用於將cpp轉成string
#define CPP_TO_STRING(word) #word

namespace GameEngine
{
    //以下用於轉換型別
    glm::vec2 vectorToVec2(const std::vector<float>& vec);
    glm::vec3 vectorToVec3(const std::vector<float>& vec);
    glm::vec4 vectorToVec4(const std::vector<float>& vec);

    template<class T>
    const T& max(const T& a, const T& b)
    {
        return (a < b) ? b : a;
    }
    template<class T, class... Args>
    const T& max(const T& a, Args... args)
    {
        return max(a, max(args...));
    }
    //用於產生亂數(無範圍)
    int randint();
    //用於產生亂數(最小值~最大值)(含尾)
    int randint(int from, int to);
    /*
        用於將array的元素洗牌( 應用Fisher-Yates algorithm O(n) )
        parameter:
            - array: 欲打亂順序的陣列
            - len: array的長度
            - size: 陣列中元素的size
            - swap: 交換函式
    */
    void shuffle(void* array, unsigned int len, size_t size, void (*swap)(void* a, void* b));
}

#endif