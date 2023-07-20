#ifndef GAMEENGINE_UUID_H
#define GAMEENGINE_UUID_H

#include <string>
#include <random>
#include <sstream>
#include <functional>

namespace GameEngine
{
    class UUID
    {
    public:
        UUID();
    private:
        uint64_t _UUID[2];
        
        friend struct std::hash<GameEngine::UUID>;
        friend std::ostream& operator<<(std::ostream& logger, const UUID &uuid);
    };
    std::ostream& operator<<(std::ostream &logger, const UUID &uuid);
} // namespace GameEngine

template<class T>
inline static void hash_combine(std::size_t& seed, const T& v)
{
    //phi = (1 + sqrt(5)) / 2
    //2^32 / phi = 0x9e3779b9
    //per bit 0 or 1 機率差不多
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
    template<>
    struct hash<GameEngine::UUID>
    {
        size_t operator()(const GameEngine::UUID& uuid) const
        {
            size_t seed = 0;
            hash_combine(seed, uuid._UUID[0]);
            hash_combine(seed, uuid._UUID[1]);
            return seed;
        }
    };
    
};

#endif