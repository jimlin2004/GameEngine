#include "../include/GameEngineAPI/ConsoleApi.h"

#include "Event/Input.h"

void GameEngine::ConsoleApi::log(const char* const format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

GameEngine::Logger &GameEngine::operator<<(GameEngine::Logger &logger, const MousePosition &mousePosition)
{
    logger << '[' << mousePosition.x << ", " << mousePosition.y << ']';
    return logger;
}