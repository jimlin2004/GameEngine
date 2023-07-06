#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"

#include "entt.hpp"
#include "Timestep.h"
#include "Renderer.h"
#include <vector>
#include <exception>
#include "GELib.h"
#include "TypeName.hpp"
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
            TActor* obj = new TActor(this->registry.create());
            return obj;
        }

        template<class TActor>
        TActor* spawnActor(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const std::string& actorName)
        {
            auto typeName_strView = TYPE_NAME_BY_TYPE(TActor);
            std::string typeName = {typeName_strView.begin(), typeName_strView.end()};
            TActor* obj = new TActor(this->registry.create(), position, scale, rotation, actorName, typeName);
            return obj;
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