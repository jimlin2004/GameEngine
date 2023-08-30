#include "Bird.h"
#include "Event/PhysicsEvent.h"
#include "Event/KeyDownEvent.h"

REGISTER_CLASS(Bird)
Bird::Bird()
    : GameEngine::Character()
{
}

void Bird::destroy()
{
}

void Bird::begin()
{
    this->body = (b2Body*)this->getComponent<GameEngine::Rigidbody2DComponent>().runtimeBody;
    
    GEngineCore::addCallback(GameEngine::EventType::CollisionEvent, [](GameEngine::Event& event){
        GameEngine::CollisionEvent& collisionEvent = dynamic_cast<GameEngine::CollisionEvent&>(event);
        printf("a: %s\n", collisionEvent.dataA->getTag().c_str());
        printf("b: %s\n", collisionEvent.dataB->getTag().c_str());
    });

    GEngineCore::addCallback(GameEngine::EventType::KeyDownEvent, [this](GameEngine::Event& event){
        GameEngine::KeyDownEvent& keyDownEvent = dynamic_cast<GameEngine::KeyDownEvent&>(event);
        if (keyDownEvent.key() == GameEngine::Key_SPACE)
        {
            this->body->SetLinearVelocity(b2Vec2(0, 5));
            // this->body->ApplyLinearImpulse(b2Vec2(0, 20), this->body->GetWorldCenter(), true);
        }
    });
}

void Bird::update(const float deltaTime)
{
}
