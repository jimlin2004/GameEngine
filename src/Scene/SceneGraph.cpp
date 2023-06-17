// #include "Scene/SceneGraph.h"

// //SceneGraphNode
// GameEngine::SceneGraphNode::SceneGraphNode(const std::string& _objectName, Actor* _actor)
//     : objectName(_objectName)
//     , actor(_actor)
// {

// }

// GameEngine::SceneGraphNode::~SceneGraphNode()
// {
//     this->components.clear();
//     delete this->actor;
// }

// const bool GameEngine::SceneGraphNode::isLeaf() const
// {
//     return (this->components.empty());
// }

// void GameEngine::SceneGraphNode::addComponent(GameEngine::Component* component)
// {
//     this->components.push_back(component);
// }

// //SceneGraph

// GameEngine::SceneGraph::SceneGraph()
// {

// }

// GameEngine::SceneGraph::~SceneGraph()
// {
//     this->sceneMap.clear();
// }

// template<class TClass>
// void GameEngine::SceneGraph::addNode(TClass obj)
// {
//     std::string objectName = GET_OBJECT_NAME(TClass);
//     SceneGraphNode* newNode = new SceneGraphNode(objectName, obj);
//     if (this->sceneMap.find(objectName) != this->sceneMap.end())
//     {
//         std::map<std::string, SceneGraphNode*>* gameObjectMap = &(this->sceneMap[objectName]);
//         gameObjectMap->insert({objectName + "_" + std::to_string(gameObjectMap->size() + 1), newNode});
        
//     }
//     else
//     {
//         this->sceneMap.insert({objectName, {}});
//         this->sceneMap[objectName].insert({objectName, newNode});
//     }
// }