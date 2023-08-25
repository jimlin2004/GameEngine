#include "Core/UUID.h"

#include <string>
#include <random>
#include <sstream>
#include <functional>
#include <cstdio>
#include <inttypes.h>

static std::random_device randomDevice;
static std::mt19937_64    randomEngine(randomDevice());
static std::uniform_int_distribution<uint64_t> distribution;

GameEngine::UUID::UUID()
    : _UUID({distribution(randomEngine), distribution(randomEngine)})
{
    //UUID version 4 like, 但非規範格式8-4-4-4-12
    //這裡用2個uint64代表
}
bool GameEngine::UUID::operator==(const GameEngine::UUID &other) const
{
    if (this->_UUID[0] == other._UUID[0])
        return this->_UUID[1] == other._UUID[1];
    return this->_UUID[0] == other._UUID[1];
}

void GameEngine::UUID::operator=(const UUID &other)
{
    this->_UUID[0] = other._UUID[0];
    this->_UUID[1] = other._UUID[1];
}

std::size_t std::hash<GameEngine::UUID>::operator()(const GameEngine::UUID &uuid) const
{
    size_t seed = 0;
    hash_combine(seed, uuid._UUID[0]);
    hash_combine(seed, uuid._UUID[1]);
    return seed;
}

void  GameEngine::to_json(GameEngine::Json &json, const GameEngine::UUID &uuid)
{
    std::string uuidData;
    char buffer[24];
    std::snprintf(buffer, sizeof(buffer), "%020" PRIu64, uuid._UUID[1]);
    uuidData += std::string(buffer);
    std::snprintf(buffer, sizeof(buffer), "%020" PRIu64, uuid._UUID[0]);
    uuidData += std::string(buffer);
    json = GameEngine::Json{
        {"UUID", uuidData}
    };
}

void  GameEngine::from_json(const GameEngine::Json &json, GameEngine::UUID &uuid)
{
    std::string uuidData = json["UUID"];
    uuid._UUID[1] = std::stoull(uuidData.substr(0, 20));
    uuid._UUID[0] = std::stoull(uuidData.substr(20, 20));
}
