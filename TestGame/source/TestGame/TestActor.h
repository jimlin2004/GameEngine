#ifndef TEST_ACTOR_H
#define TEST_ACTOR_H

#include "Core/GameEngineCore.h"
#include "box2d/b2_body.h"

class GENGINE_API TestActor: public GameEngine::Character
{
public:
    TestActor();
    virtual void destroy() override;
    virtual void begin() override;
    virtual void update(const float deltaTime) override;
private:
    b2Body* body;
};

#endif