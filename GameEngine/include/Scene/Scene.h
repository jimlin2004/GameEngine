#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"

#include "entt.hpp"
#include "Core/Timestep.h"
#include <vector>
#include <exception>
#include "Core/GELib.h"
#include "Core/TypeName.hpp"
#include <iostream>

namespace GameEngine
{
    class Scene
    {
    public:
        entt::registry registry;
        Scene();
        ~Scene();
        void unpdateScene(const float deltaTime);
        void render();
        std::vector<entt::entity> getAllActors();
        template<class TActor>
        TActor* spawnActor()
        {
            TActor* obj = new TActor();
            obj->setEntityID(this->registry.create());
            return obj;
        }

        template<class TActor>
        TActor* spawnActor(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const std::string& actorName)
        {
            auto typeName_strView = TYPE_NAME_BY_TYPE(TActor);
            std::string typeName = {typeName_strView.begin(), typeName_strView.end()};
            TActor* obj = new TActor();
            obj->setEntityID(this->registry.create());
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
    };

    //整個遊戲引擎的global pointer，勿修改
    extern Scene* globalScene;
}

#endif