#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"

#include "SceneGraph.h"
#include "Timestep.h"

namespace GameEngine
{
    class Scene
    {
    private:
        SceneGraph* sceneGraph;
    public:
        Scene();
        ~Scene();
        void unpdateScene(const float deltaTime);
        void render();
        template<class TActor>
        TActor* spawnActor(const glm::vec3& position);
        template<class TActor>
        TActor* spawnActor(const glm::vec3& position, const glm::vec2& size);
    };
}

#endif