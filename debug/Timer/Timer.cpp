#include "Timer.h"

Timer::Timer()
{
    this->startTimePoint = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoint = std::chrono::high_resolution_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(this->startTimePoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();
    GameEngine::ConsoleApi::log("Duration: %f ms\n", (end - start) * 0.001f);
}