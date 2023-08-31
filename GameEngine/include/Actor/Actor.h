#ifndef GE_ACTOR_H
#define GE_ACTOR_H

#include "glm/glm.hpp"
#include "Core/GameObject.h"
#include "entt.hpp"
#include "Scene/Scene.h"
#include "Core/UUID.h"
#include <string>

namespace GameEngine
{
    //遊戲中的角色基類(不可使用Input event)
    class Actor: public GameObject
    {
    protected:
        Scene* scene;
        entt::entity entityID;        
    public:
        Actor();
        Actor(Actor& other);
        Actor(entt::entity entityID, Scene* scenePtr);
        Actor(entt::entity entityID, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const std::string& actorName, const std::string& typeName);
        virtual ~Actor();

        void bindScene(GameEngine::Scene* newScene);

        // User should not use
        void setEntityID(entt::entity entityID);
        
        // User should not use
        void initComponents(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const std::string& actorName, const std::string& typeName);
        // User should not use
        void initIDComponent(const UUID& uuid);

        virtual void begin();
        virtual void update(const float deltaTime);
        virtual void destroy();
        
        // User should not use
        inline uint32_t getID() const
        {
            return (uint32_t)this->entityID;
        }
        
        // User should not use
        inline Scene* getScenePtr() const
        {
            return this->scene;
        }
        
        UUID getUUID();

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

        operator bool();
    };
}

#endif