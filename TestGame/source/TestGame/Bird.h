#ifndef BIRD_H
#define BIRD_H

#include "Core/GameEngineCore.h"
#include "box2d/b2_body.h"

class GENGINE_API Bird: public GameEngine::Character
{
public:
    Bird();
    virtual void destroy() override;
    virtual void begin() override;
    virtual void update(const float deltaTime) override;
private:
    b2Body* body;
};

#endif