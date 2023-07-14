#ifndef GE_ACTOR_H
#define GE_ACTOR_H

#include "Core/GameObject.h"
#include "Core/Timestep.h"
#include "entt.hpp"
#include "Scene/Scene.h"
#include <exception>
#include <string>

namespace GameEngine
{
    //遊戲中的角色基類(不可使用Input event)
    class Actor: public GameObject
    {
    protected:
        static Scene* scene;
        entt::entity entityID;        
    public:
        Actor();
        Actor(Actor& other);
        Actor(entt::entity entityID);
        Actor(entt::entity entityID, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const std::string& actorName, const std::string& typeName);

        static void bindScene(GameEngine::Scene* newScene);

        // User should not use
        virtual void setEntityID(entt::entity entityID);
        // User should not use
        void initComponents(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const std::string& actorName, const std::string& typeName);

        virtual ~Actor();
        virtual void HandleEvent();
        //渲染
        virtual void render();
        //設定角色在世界的位置
        virtual void setPosition(float x, float y);
        virtual void begin();
        virtual void update(const float deltaTime);
        virtual void destroy();

        inline uint32_t getID() const
        {
            return (uint32_t)this->entityID;
        }

        template <class T>
        bool hasComponent()
        {
            return this->scene->registry.all_of<T>(this->entityID);
        }

        template <class T, class... Args>
        T& addComponent(Args&&... args)
        {
            if (this->hasComponent<T>())
                throw std::invalid_argument("The actor already has component");
            return this->scene->registry.emplace<T>(this->entityID, std::forward<Args>(args)...);
        }

        template <class T>
        T& getComponent()
        {
            if (!this->hasComponent<T>())
                throw std::invalid_argument("The actor does not have component");
            return this->scene->registry.get<T>(this->entityID);
        }

        template <class T>
        void removeComponent()
        {
            if (!this->hasComponent<T>())
                throw std::invalid_argument("The actor does not have component");
            this->scene->registry.remove<T>(this->entityID);
        }
    };

    //可編程
    class Character: public Actor
    {
    public:
        Character();
        virtual ~Character();
        // User should not use
        virtual void setEntityID(entt::entity entityID) override;
    };
}

#endif