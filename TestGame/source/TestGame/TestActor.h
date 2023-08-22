#ifndef TEST_ACTOR_H
#define TEST_ACTOR_H

#include "Script/ScriptEngineMacro.h"
#include "Script/ClassMap.h"
#include "Actor/Actor.h"
#include "Event/Input.h"
#include "Component/Component.h"

class GENGINE_API TestActor: public GameEngine::Actor
{
public:
    TestActor();
    virtual void destroy() override;
    virtual void begin() override;
    virtual void update(const float deltaTime) override;
};

#endif