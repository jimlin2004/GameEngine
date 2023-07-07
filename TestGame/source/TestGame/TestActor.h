#ifndef TEST_ACTOR_H
#define TEST_ACTOR_H

#include "Core/GameEngineCore.h"

class TestActor: public GameEngine::Character
{
public:
    TestActor();
    virtual void destroy() override;
    virtual void begin() override;
    virtual void update(const float deltaTime) override;
};

#endif