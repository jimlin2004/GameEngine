#include "Actor.h"

GameEngine::Actor::Actor()
    : entityID()
{
    this->initComponents();
}

GameEngine::Actor::Actor(Actor &other)
    : entityID(other.entityID)
{
}

GameEngine::Actor::Actor(entt::entity entityID, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation)
    : entityID(entityID)
{
    this->initComponents(position, scale, rotation);
}

GameEngine::Actor::~Actor()
{
}

void GameEngine::Actor::initComponents(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation)
{
    this->addComponent<GameEngine::TransformComponent>(position, scale, rotation);
    this->addComponent<GameEngine::MeshComponent>();
    this->addComponent<GameEngine::TagComponent>();
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

GameEngine::Character::Character()
    : GameEngine::Actor()
{
}

GameEngine::Character::~Character()
{
}

void GameEngine::Character::setInputEvent()
{
}

namespace GameEngine
{
    Scene* Actor::scene = globalScene;
}