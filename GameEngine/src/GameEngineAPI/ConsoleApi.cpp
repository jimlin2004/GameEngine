#include "GameEngineAPI/ConsoleApi.h"

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
GameEngine::Logger &GameEngine::operator<<(GameEngine::Logger &logger, const UUID &uuid)
{
    logger << uuid._UUID[0] << uuid._UUID[1];
    return logger;
}