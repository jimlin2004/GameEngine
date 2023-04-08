#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include <list>
#include <string>

#include "GameObject.h"

namespace GameEngine
{
    class SceneGraphNode
    {
    public:
        std::list<SceneGraphNode*> chilren;
    private:
        std::string objectName;
        GameEngine::GameObject* gameObject;
    public:
        SceneGraphNode(const std::string& _objectName);
        ~SceneGraphNode();
        const bool isLeaf() const;
        void addNewNode(SceneGraphNode* node);
    };

    // 基本為tree(多叉)
    class SceneGraph
    {
    public:
        SceneGraphNode* root;
    public:
        SceneGraph();
    };
}


#endif