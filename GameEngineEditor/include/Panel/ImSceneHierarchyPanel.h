#ifndef IMSCENE_CONTENT_H
#define IMSCENE_CONTENT_H

#include "Scene/Scene.h"
#include "Actor/Actor.h"

namespace GameEngineEditor
{
    class ImSceneHierarchyPanel
    {
    public:
        ImSceneHierarchyPanel();
        void setScene(GameEngine::Scene* scene);
        void render();
        void setSelectedEntityID(uint32_t entityID);
        inline uint32_t getSelectedEntityID() const { return this->selectedEntity; }
    private:
        GameEngine::Scene* scene;
        uint32_t selectedEntity;

        void renderActorNode(GameEngine::Actor& actor);
    };
}

#endif