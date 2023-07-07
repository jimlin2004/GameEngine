#ifndef BST_H
#define BST_H

//未完工

namespace GameEngine
{

    template<class T>
    class BST_Node
    {
    public:
        T data;
        BST_Node* left, *right;
        BST_Node();
        BST_Node(const T& _data);
        BST_Node(const BST_Node& node);
    };

    // BST(非AVL)
    // 用operator < 做比較
    template<class T>
    class BST
    {
    private:
        BST_Node<T>* root;
        void _insert(BST_Node<T>** root, const T& _data);
    public:
        BST();
        void insert(const T& _data);
        T* query(const T& _data);
    };

}


#endif