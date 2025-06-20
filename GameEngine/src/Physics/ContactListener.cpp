#include "Physics/ContactListener.h"

GameEngine::ContactListener::ContactListener()
    : b2ContactListener()
    , beginContactPtr([](b2Contact*){})
    , endContactPtr([](b2Contact*){})
{
}

GameEngine::ContactListener::~ContactListener()
{
}

void GameEngine::ContactListener::BeginContact(b2Contact *contact)
{
    this->beginContactPtr(contact);
}

void GameEngine::ContactListener::EndContact(b2Contact *contact)
{
    this->endContactPtr(contact);
}

void GameEngine::ContactListener::setBeginContact(std::function<void(b2Contact *)> funcPtr)
{
    this->beginContactPtr = funcPtr;
}

void GameEngine::ContactListener::setEndContact(std::function<void(b2Contact *)> funcPtr)
{
    this->endContactPtr = funcPtr;
}
