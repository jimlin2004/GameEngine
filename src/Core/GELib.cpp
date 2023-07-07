#include "Core/GELib.h"

int GameEngine::randint()
{
    srand(time(NULL));
    return rand();
}

int GameEngine::randint(int from, int to)
{
    srand(time(NULL));
    return rand() % (to - from + 1) + from;
}

void GameEngine::shuffle(void* array, unsigned int len, size_t size, void (*swap)(void* a, void* b))
{
    int randN;
    int offset1;
    int offset2;
    for (unsigned int i = len - 1; i >= 1; --i)
    {
        randN = GameEngine::randint(0, i);
        swap((char*)array + size * i, (char*)array + size * randN);
    }
    return;
}