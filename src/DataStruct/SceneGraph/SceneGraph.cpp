#include "DataStruct/SceneGraph/SceneGraph.h"

//SceneGraphNode
GameEngine::SceneGraphNode::SceneGraphNode(const std::string& _objectName)
    :objectName(_objectName)
{

}

GameEngine::SceneGraphNode::~SceneGraphNode()
{
    this->chilren.clear();
    delete this->gameObject;
}

const bool GameEngine::SceneGraphNode::isLeaf() const
{
    return (this->chilren.empty());
}

void GameEngine::SceneGraphNode::addNewNode(GameEngine::SceneGraphNode* node)
{
    this->chilren.push_back(node);
}

//SceneGraph

GameEngine::SceneGraph::SceneGraph()
    :root(new GameEngine::SceneGraphNode("world"))
{

}