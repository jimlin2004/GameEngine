#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include "Actor.h"
#include "Scene/Scene.h"
#include "glm/glm.hpp"

class EditorScene
{
public:
    EditorScene();
    ~EditorScene();
    template <class T>
    static void addActor(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation)
    {
        GameEngine::globalScene->spawnActor<T>(position, scale, rotation);
    }
};

#endif