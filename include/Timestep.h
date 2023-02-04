#ifndef TIMESTEP_H
#define TIMESTEP_H

#include <stdint.h>

namespace GameEngine
{
    class Timestep
    {
    private:
        float time;
    public:
        Timestep(float time = 0);
        operator float() const;
        inline float getSeconds() const;
        inline float getMilliseconds() const;
    };
}

#endif