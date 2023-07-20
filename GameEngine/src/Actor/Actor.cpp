#include "Actor/Actor.h"

#include "Component/Component.h"

GameEngine::Actor::Actor()
    : entityID(entt::null)
{
}

GameEngine::Actor::Actor(Actor &other)
    : entityID(other.entityID)
{
}

GameEngine::Actor::Actor(entt::entity entityID)
    : entityID(entityID)
{
}

GameEngine::Actor::Actor(entt::entity entityID, const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation, const std::string &actorName, const std::string &typeName)
    : entityID(entityID)
{
    this->initComponents(position, scale, rotation, actorName, typeName);
}

void GameEngine::Actor::bindScene(GameEngine::Scene *newScene)
{
    GameEngine::Actor::scene = newScene;
}

void GameEngine::Actor::setEntityID(entt::entity entityID)
{
    this->entityID = entityID;
}

void GameEngine::Actor::initComponents(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation, const std::string &actorName, const std::string &typeName)
{
    this->addComponent<GameEngine::TransformComponent>(position, scale, rotation);
    this->addComponent<GameEngine::MeshComponent>();
    this->addComponent<GameEngine::TagComponent>(actorName, typeName);
}

GameEngine::Actor::~Actor()
{
    this->destroy();
}

void GameEngine::Actor::HandleEvent()
{
}

void GameEngine::Actor::render()
{
}

void GameEngine::Actor::setPosition(float x, float y)
{
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

GameEngine::Character::Character()
    : GameEngine::Actor()
{
}

GameEngine::Character::~Character()
{
}

void GameEngine::Character::setEntityID(entt::entity entityID)
{
    this->entityID = entityID;
    GameEngine::ScriptComponent& scriptComponent = this->addComponent<GameEngine::ScriptComponent>();
    scriptComponent.instance = this;
}
namespace GameEngine
{
    Scene* Actor::scene = globalScene;
}