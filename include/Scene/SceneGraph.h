// #ifndef SCENE_GRAPH_H
// #define SCENE_GRAPH_H

// #include <list>
// #include <map>
// #include <string>

// #include "GameObject.h"
// #include "Actor.h"
// #include "Component.h"

// // 將SpawnActor的TActor變文字 c++ script to string
// #define GET_OBJECT_NAME(TClass) #TClass 

// namespace GameEngine
// {
//     class SceneGraphNode
//     {
//     public:
//         std::list<Component*> components;
//         std::string objectName;
//         Actor* actor;
        
//         SceneGraphNode(const std::string& _objectName, Actor* _actor);
//         ~SceneGraphNode();
//         const bool isLeaf() const;
//         void addComponent(Component* component);
//     };
//     /* 
//         基本為tree(多叉)
//         用map連結各個Node(物件種類)的樹
//         每個Node再包含一個std::map(用以快速插入、排序、查詢，key是objectName)用以處理物件名衝突問題(以1, 2, 3...作區別)
//         map裡的value才是真正的GameObject
//         每個SceneGraphNode的child為他們的Component
//     */
//     class SceneGraph
//     {
//     private:
//         std::map<std::string, std::map<std::string, SceneGraphNode*>> sceneMap;
//     public:
//         SceneGraph();
//         ~SceneGraph();

//         template<class TClass>
//         void addNode(TClass obj);
//         friend class Scene;
//     };
// }


// #endif