#include "DataStruct/BST/BST.h"

template<class T>
GameEngine::BST_Node<T>::BST_Node()
    : data(T())
    , left(nullptr)
    , right(nullptr)
{

}

template<class T>
GameEngine::BST_Node<T>::BST_Node(const T& _data)
    : data(_data)
    , left(nullptr)
    , right(nullptr)
{

}

template<class T>
GameEngine::BST_Node<T>::BST_Node(const BST_Node& node)
    : data(node->data)
    , left(node->left)
    , right(node->right)
{

}

// BST

template<class T>
GameEngine::BST<T>::BST()
    : root(nullptr)
{

}

template<class T>
void GameEngine::BST<T>::_insert(BST_Node<T>** root, const T& _data)
{
    // if (!(*root))
    // {
    //     (*root) = new BST_Node<T>();
    //     return ;
    // }
    // if ((*root)->data < _data)
    //     (*root)->
}

template<class T>
void GameEngine::BST<T>::insert(const T& _data)
{
    // this->_insert()
}