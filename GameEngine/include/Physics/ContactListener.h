#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include "box2d/b2_world_callbacks.h"
#include <functional>

namespace GameEngine
{
    class ContactListener: public b2ContactListener
    {
    public:
        explicit ContactListener();
        virtual ~ContactListener();

        virtual void BeginContact(b2Contact* contact) override;
        virtual void EndContact(b2Contact* contact) override;
    
        void setBeginContact(std::function<void(b2Contact*)> funcPtr);
        void setEndContact(std::function<void(b2Contact*)> funcPtr);
    private:
        std::function<void(b2Contact*)> beginContactPtr = nullptr;
        std::function<void(b2Contact*)> endContactPtr = nullptr;
    };
}

#endif