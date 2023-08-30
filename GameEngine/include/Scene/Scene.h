#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"

#include "Core/UUID.h"
#include "entt.hpp"
#include <vector>
#include <exception>
#include "Core/TypeName.hpp"

class b2World;

namespace GameEngine
{
    class ContactListener;
    
    class Scene
    {
    public:
        entt::registry registry;
        explicit Scene();
        ~Scene();
        void unpdateRuntimeScene(const float deltaTime);
        void render();
        std::vector<entt::entity> getAllActors();

        static Scene* copy(Scene* other);
        void onRuntimeStart();
        void onRunTimeStop();

        template<class TActor>
        TActor* spawnActor()
        {
            TActor* obj = new TActor();
            obj->setEntityID(this->registry.create());
            obj->bindScene(this);
            return obj;
        }

        template<class TActor>
        TActor* spawnActor(const UUID& uuid)
        {
            TActor* obj = new TActor();
            obj->setEntityID(this->registry.create());
            obj->bindScene(this);
            obj->initIDComponent(uuid);
            return obj;
        }

        template<class TActor>
        TActor* spawnActor(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const std::string& actorName)
        {
            auto typeName_strView = TYPE_NAME_BY_TYPE(TActor);
            std::string typeName = {typeName_strView.begin(), typeName_strView.end()};
            TActor* obj = new TActor();
            obj->setEntityID(this->registry.create());
            obj->bindScene(this);
            obj->initComponents(position, scale, rotation, actorName, typeName);
            return obj;
        }

        template<class T>
        bool actorHasComponent(entt::entity entityID)
        {
            return (this->registry.all_of<T>(entityID));
        }

        template<class T> 
        T& queryActorComponent(entt::entity entityID)
        {
            if (!this->registry.all_of<T>(entityID))
                throw std::invalid_argument("The actor does not have component");
            return this->registry.get<T>(entityID);
        }
    private:
        b2World* physicsWorld;
        ContactListener* contactListener;
    };

    //整個遊戲引擎的global pointer，勿修改
    extern Scene* globalScene;
}

#endif