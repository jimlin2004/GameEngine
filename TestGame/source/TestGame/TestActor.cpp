#include "TestActor.h"
#include "Event/PhysicsEvent.h"
#include "Event/KeyDownEvent.h"

REGISTER_CLASS(TestActor)
TestActor::TestActor()
    : GameEngine::Character()
{
}

void TestActor::destroy()
{
}

void TestActor::begin()
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
            this->body->SetLinearVelocity(b2Vec2(0, 10));
            // this->body->ApplyForce(b2Vec2(0, 2000), this->body->GetWorldCenter(), true);
        }
    });
}

void TestActor::update(const float deltaTime)
{
    GameEngine::TransformComponent& transform = this->getComponent<GameEngine::TransformComponent>();
    // GameEngine::MeshComponent& mesh = this->getComponent<GameEngine::MeshComponent>();
    // mesh.color.r = 0;
    if (GEngineCore::Input::isKeyPressed(GameEngine::Key_A))
        transform.translation.x -= (10.0f * deltaTime);
    if (GEngineCore::Input::isKeyPressed(GameEngine::Key_D))
        transform.translation.x += (10.0f * deltaTime);
    if (GEngineCore::Input::isKeyPressed(GameEngine::Key_W))
        transform.translation.y += (10.0f * deltaTime);
    if (GEngineCore::Input::isKeyPressed(GameEngine::Key_S))
        transform.translation.y -= (10.0f * deltaTime);
    // if (GEngineCore::Input::isKeyPressed(GameEngine::Key_SPACE))
    // {
    //     b2Body* body = (b2Body*)this->getComponent<GameEngine::Rigidbody2DComponent>().runtimeBody;
    //     printf("space\n");
    //     body->ApplyLinearImpulse(b2Vec2(0, 5), body->GetWorldCenter(), true);
    // }
}