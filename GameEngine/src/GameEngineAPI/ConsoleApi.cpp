#include "../include/GameEngineAPI/ConsoleApi.h"

void GameEngine::ConsoleApi::log(const char* const format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}