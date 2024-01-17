#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include "Scene/Scene.h"
#include "glm/glm.hpp"
#include "Actor/Actor.h"
#include <vector>

class EditorScene
{
public:
    template <class T>
    static inline void addActor(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const std::string& actorName)
    {
        GameEngine::globalScene->spawnActor<T>(position, scale, rotation, actorName);
    }
    static inline std::vector<entt::entity> getAllActors()
    {
        return GameEngine::globalScene->getAllActors();
    }
};

#endif