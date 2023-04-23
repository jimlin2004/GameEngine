#include "DataStruct/SceneGraph/SceneGraph.h"

//SceneGraphNode
GameEngine::SceneGraphNode::SceneGraphNode(const std::string& _objectName, GameObject* obj)
    : objectName(_objectName)
    , gameObject(obj)
{

}

GameEngine::SceneGraphNode::~SceneGraphNode()
{
    this->components.clear();
    delete this->gameObject;
}

const bool GameEngine::SceneGraphNode::isLeaf() const
{
    return (this->components.empty());
}

void GameEngine::SceneGraphNode::addComponent(GameEngine::Component* component)
{
    this->components.push_back(component);
}

//SceneGraph

GameEngine::SceneGraph::SceneGraph()
{

}

GameEngine::SceneGraph::~SceneGraph()
{
    this->table.clear();
}