#ifndef IMPROPERTIES_H
#define IMPROPERTIES_H

#include "Scene/Scene.h"
#include "entt.hpp"

namespace GameEngineEditor
{
    class ImPropertiesPanel
    {
    public:
        void render(entt::entity entityID, GameEngine::Scene* scene);
    };
}

#endif