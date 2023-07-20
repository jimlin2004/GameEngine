#include "Core/UUID.h"

static std::random_device randomDevice;
static std::mt19937_64    randomEngine(randomDevice());
static std::uniform_int_distribution<uint64_t> distribution;

GameEngine::UUID::UUID()
    : _UUID({distribution(randomEngine), distribution(randomEngine)})
{
    //UUID version 4 like, 但非規範格式8-4-4-4-12
    //這裡用2個uint64代表
}