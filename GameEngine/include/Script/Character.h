#ifndef CHARACTER_H
#define CHARACTER_H

#include "Actor/Actor.h"

namespace GameEngine
{
    class Character
    {
    public:
        explicit Character();
        virtual ~Character();
        virtual void destroy() = 0;
        virtual void begin() = 0;
        virtual void update(const float deltaTime) = 0;

        void createActor(entt::entity entityID, Scene* scenePtr);
        template<class Component>
        Component& getComponent()
        {
            return this->actor->getComponent<Component>();
        }
    private:
        Actor* actor;
    };
}

#endif