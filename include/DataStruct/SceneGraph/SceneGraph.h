#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include <list>
#include <map>
#include <string>

#include "GameObject.h"
#include "ActorComponent/Component/Component.h"

// 將SpawnActor的TActor變文字 c++ script to string
#define GET_OBJECT_NAME(TClass) #TClass 

namespace GameEngine
{
    class SceneGraphNode
    {
    public:
        std::list<Component*> components;
    private:
        std::string objectName;
        GameObject* gameObject;
    public:
        SceneGraphNode(const std::string& _objectName, GameObject* obj);
        ~SceneGraphNode();
        const bool isLeaf() const;
        void addComponent(Component* component);
    };

    // 基本為tree(多叉)
    // 用map連結各個Node的樹
    // 每個SceneGraphNode的child為他們的Component
    class SceneGraph
    {
    private:
        std::map<std::string, SceneGraphNode*> table;
    public:
        SceneGraph();
        ~SceneGraph();

        template<class TClass>
        void addNode(TClass obj)
        {
            SceneGraphNode* newNode = new SceneGraphNode(GET_OBJECT_NAME(TClass), obj);
            this->table.insert({GET_OBJECT_NAME(TClass), newNode});
        }
    };
}


#endif