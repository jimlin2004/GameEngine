#ifndef IMPROPERTIES_H
#define IMPROPERTIES_H

#include "Scene/Scene.h"
#include "entt.hpp"
#include <filesystem>

namespace GameEngineEditor
{
    class ImPropertiesPanel
    {
    public:
        void render(entt::entity entityID, GameEngine::Scene* scene);
        void setRootPath(const std::filesystem::path& newPath);
    private:
        std::filesystem::path rootPath;
    };
}

#endif