#ifndef IMSCENE_CONTENT_H
#define IMSCENE_CONTENT_H

#include "Scene/Scene.h"
#include "Actor/Actor.h"

namespace GameEngineEditor
{
    class ImSceneHierarchy
    {
    public:
        ImSceneHierarchy();
        void setScene(GameEngine::Scene* scene);
        void render();
        void setSelectedEntity(uint32_t entityID);
    private:
        GameEngine::Scene* scene;
        uint32_t selectedEntity;

        void renderActorNode(GameEngine::Actor& actor);
    };
}

#endif