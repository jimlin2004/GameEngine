#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include "../../include/GameEngineAPI/ConsoleApi.h"

class Timer
{
public:
    Timer();
    ~Timer();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
};

#endif