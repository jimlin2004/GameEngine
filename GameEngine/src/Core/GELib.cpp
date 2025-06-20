#include "Core/GELib.h"

glm::vec2 GameEngine::vectorToVec2(const std::vector<float>& vec)
{
    return {vec[0], vec[1]};
}

glm::vec3 GameEngine::vectorToVec3(const std::vector<float> &vec)
{
    return {vec[0], vec[1], vec[2]};
}

glm::vec4 GameEngine::vectorToVec4(const std::vector<float> &vec)
{
    return {vec[0], vec[1], vec[2], vec[3]};
}

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
    for (unsigned int i = len - 1; i >= 1; --i)
    {
        randN = GameEngine::randint(0, i);
        swap((char*)array + size * i, (char*)array + size * randN);
    }
    return;
}