#include "Actor/Actor.h"

#include <exception>
#include "Component/Component.h"

GameEngine::Actor::Actor()
    : entityID(entt::null)
    , scene(nullptr)
{
}

GameEngine::Actor::Actor(Actor &other)
    : entityID(other.entityID)
    , scene(other.scene)
{
}

GameEngine::Actor::Actor(entt::entity entityID, Scene* scenePtr)
    : entityID(entityID)
    , scene(scenePtr)
{
}

GameEngine::Actor::Actor(entt::entity entityID, const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation, const std::string &actorName, const std::string &typeName)
    : entityID(entityID)
{
    this->initComponents(position, scale, rotation, actorName, typeName);
}

void GameEngine::Actor::bindScene(GameEngine::Scene *newScene)
{
    this->scene = newScene;
}

void GameEngine::Actor::setEntityID(entt::entity entityID)
{
    this->entityID = entityID;
}

void GameEngine::Actor::initComponents(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation, const std::string &actorName, const std::string &typeName)
{
    this->addComponent<GameEngine::IDComponent>();
    this->addComponent<GameEngine::TransformComponent>(position, scale, rotation);
    this->addComponent<GameEngine::MeshComponent>();
    this->addComponent<GameEngine::TagComponent>(actorName, typeName);
}

void GameEngine::Actor::initIDComponent(const UUID &uuid)
{
    this->addComponent<GameEngine::IDComponent>(uuid);
}

GameEngine::Actor::~Actor()
{
    this->destroy();
}

void GameEngine::Actor::begin()
{
}

void GameEngine::Actor::update(const float deltaTime)
{
}

void GameEngine::Actor::destroy()
{
}

GameEngine::UUID GameEngine::Actor::getUUID()
{
    return this->getComponent<GameEngine::IDComponent>().uuid;
}
GameEngine::Actor::operator bool()
{
    return (this->entityID != entt::null);
}