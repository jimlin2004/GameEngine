#include "Physics/ActorData.h"

#include "Component/Component.h"

GameEngine::ActorData::ActorData(entt::entity entityID, Scene *scenePtr)
    : actor(entityID, scenePtr)
{
}

GameEngine::ActorData::~ActorData()
{
}

std::string GameEngine::ActorData::getTag()
{
    return actor.getComponent<GameEngine::TagComponent>().tagName;
}