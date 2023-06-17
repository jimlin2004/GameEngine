#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"

#include "entt.hpp"
#include "Timestep.h"
#include "Component/Component.h"
#include "Renderer.h"

namespace GameEngine
{
    class Scene
    {
    public:
        Scene();
        ~Scene();
        void unpdateScene(const float deltaTime);
        void render();
        template<class TActor>
        TActor* spawnActor()
        {
            TActor* obj = new TActor();
            return obj;
        }

        template<class TActor>
        TActor* spawnActor(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation)
        {
            TActor* obj = new TActor(this->registry.create(), position, scale, rotation);
            return obj;
        }
        entt::registry registry;
    };

    //整個遊戲引擎的global pointer，勿修改
    extern Scene* globalScene;
}

#endif