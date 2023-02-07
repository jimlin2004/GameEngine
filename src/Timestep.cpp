#include "Timestep.h"

GameEngine::Timestep::Timestep(float time/* = 0*/)
    : time(time)
{

}

GameEngine::Timestep::operator float() const
{
    return this->time;
}

float GameEngine::Timestep::getSeconds() const
{
    return this->time;
}

float GameEngine::Timestep::getMilliseconds() const
{
    return this->time * 1000.0f;
}