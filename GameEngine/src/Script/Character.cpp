#include "Script/Character.h"

#include "Actor/Actor.h"

GameEngine::Character::Character()
{
}

GameEngine::Character::~Character()
{
    delete this->actor;
}

void GameEngine::Character::createActor(entt::entity entityID, Scene *scenePtr)
{
    this->actor = new Actor();
    this->actor->setEntityID(entityID);
    this->actor->bindScene(scenePtr);
}
