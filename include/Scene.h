#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"

#include "DataStruct/SceneGraph/SceneGraph.h"

namespace GameEngine
{
    class Scene
    {
    private:
        SceneGraph* sceneGraph;
    public:
        Scene();
        ~Scene();
        void unpdateScene();
        template<class TActor>
        TActor* spawnActor(const glm::vec3& position)
        {
            TActor* obj = new TActor(position.x, position.y);
            return obj;
        }
        template<class TActor>
        TActor* spawnActor(const glm::vec3& position, const glm::vec2& size)
        {
            TActor* obj = new TActor(position.x, position.y, size.x, size.y);
            return obj;
        }
    };
}

#endif