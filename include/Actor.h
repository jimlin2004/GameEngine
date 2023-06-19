#ifndef GE_ACTOR_H
#define GE_ACTOR_H

#include "GameObject.h"
#include "Timestep.h"
#include "entt/include/entt.hpp"
#include "Scene/Scene.h"
#include "Component/Component.h"
#include <exception>

namespace GameEngine
{
    //遊戲中的角色基類(不可使用Input event)
    class Actor: public GameObject
    {
    protected:
        static Scene* scene;
        entt::entity entityID;        
        virtual void initComponents(const glm::vec3& position = {0.0f, 0.0f, 0.0f}, const glm::vec3& scale = {1.0f, 1.0f, 1.0f}, const glm::vec3& rotation = {0.0f, 0.0f, 0.0f}, const std::string& actorName = "gameObject", const std::string& type = "undefind");
    public:
        Actor();
        Actor(Actor& other);
        Actor(entt::entity entityID, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const std::string& actorName, const std::string& type);

        virtual ~Actor();
        virtual void HandleEvent();
        //渲染
        virtual void render();
        //設定角色在世界的位置
        virtual void setPosition(float x, float y);
        virtual void begin();
        virtual void update(const float deltaTime);

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

    //可操作的角色(支援Input event)
    class Character: public Actor
    {
    public:
        Character();
        virtual ~Character();
        virtual void setInputEvent();
    // protected:
        //負責註冊InputEvent的Component
        // InputComponent* playerInputComponent;
    };
}

#endif