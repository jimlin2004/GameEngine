#ifndef BIRD_H
#define BIRD_H

#include "Core/GameEngineCore.h"
class GENGINE_API Bird: public GameEngine::Character
{
public:
    Bird();
    virtual void destroy() override;
    virtual void begin() override;
    virtual void update(const float deltaTime) override;
};

#endif