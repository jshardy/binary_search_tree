#pragma once
#include <queue>
#include "BST_Node.h"

using std::queue;

template <typename T>
class BST_Tree
{
public:
    BST_Tree();
    BST_Tree(const BST_Tree<T> &copy);
    BST_Tree &operator=(const BST_Tree<T> &copy);
    ~BST_Tree();

    void Insert(T data);
    void Delete(T data);
    int Height();

    void BreadthFirst(void(*visit)(T data));

    void InOrderTraversal(void(*visit)(T data));
    void PreOrderTraversal(void(*visit)(T data));
    void PostOrderTraversal(void(*visit)(T data));

protected:
    BST_Node<T> *m_root;

    void copy_tree(BST_Node<T> *&copy_to, const BST_Node<T> *copy_from);

    void Purge(BST_Node<T> *&node);
    void Insert(BST_Node<T> *&node, T data);
    void Delete(BST_Node<T> *&node, T data);
    int Height(BST_Node<T> *node);

    void InOrderTraversal(void(*visit)(T data), BST_Node<T> *node);
    void PreOrderTraversal(void(*visit)(T data), BST_Node<T> *node);
    void PostOrderTraversal(void(*visit)(T data), BST_Node<T> *node);
};

template <typename T>
BST_Tree<T>::BST_Tree() : m_root(NULL)
{

}

template <typename T>
BST_Tree<T>::BST_Tree(const BST_Tree<T> &copy)
{
    copy_tree(m_root, copy.m_root);
}

template <typename T>
BST_Tree<T> &BST_Tree<T>::operator=(const BST_Tree<T> &copy)
{
    if(this != &copy)
    {
        Purge();
        copy_tree(m_root, copy.m_root);
    }
    return *this;
}

template <typename T>
void BST_Tree<T>::copy_tree(BST_Node<T> *&copy_to, const BST_Node<T> *copy_from)
{
    if(copy_from)
    {
        copy_to = new BST_Node<T>(copy_from->m_data);

        if(copy_from->m_left)
            copy_tree(copy_to->m_left, copy_from->m_left);

        if(copy_from->m_right)
            copy_tree(copy_to->m_right, copy_from->m_right);
    }
}

template <typename T>
BST_Tree<T>::~BST_Tree()
{
    Purge(m_root);
}

template <typename T>
void BST_Tree<T>::Purge(BST_Node<T> *&node)
{
    if(node)
    {
        Purge(node->m_left);
        Purge(node->m_right);
        delete node;
        node = NULL;
    }
}

template <typename T>
void BST_Tree<T>::Insert(T data)
{
    Insert(m_root, data);
}

template <typename T>
void BST_Tree<T>::Insert(BST_Node<T> *&node, T data)
{
    if(!node)
        node = new BST_Node<T>(data);
    else if(data < node->m_data)
        Insert(node->m_left, data);
    else if(data > node->m_data)    //being explicit just for my mind
        Insert(node->m_right, data);
}

template <typename T>
void BST_Tree<T>::Delete(T data)
{
    Delete(m_root, data);
}

template <typename T>
void BST_Tree<T>::Delete(BST_Node<T> *&node, T data)
{
    if(node)
    {
        if(data < node->m_data)
            Delete(node->m_left, data);
        else if(data > node->m_data)
            Delete(node->m_right, data);
        else // equal
        {
            BST_Node<T> *trail = NULL;

            if(!node->m_left && !node->m_right) //two nulls
            {
                delete node;
                node = NULL;
            }
            else if(!node->m_right) //right NULL
            {
                trail = node->m_left;
                delete node;
                node = trail;
            }
            else if(!node->m_left) //left NULL
            {
                trail = node->m_right;
                delete node;
                node = trail;
            }
            else // two children - this portion is recursive - pay attention
            {
                trail = node->m_left;
                BST_Node<T> *previous = NULL;

                while(trail->m_right)
                {
                    previous = trail;
                    trail = trail->m_right;
                }

                if(!previous)
                    node->m_left = trail->m_left;
                else if(previous)
                    previous->m_right = trail->m_left;

                node->m_data = trail->m_data;
                Delete(trail, trail->m_data);
            }
        }
    }
}

template <typename T>
void BST_Tree<T>::BreadthFirst(void(*visit)(T data))
{
    queue<BST_Node<T>*> queue;
    BST_Node<T> *travel = m_root;

    if(travel)
    {
        queue.push(travel);

        while(!queue.empty())
        {
            travel = queue.front();
            queue.pop();

            if(travel->m_left)
                queue.push(travel->m_left);
            if(travel->m_right)
                queue.push(travel->m_right);

            visit(travel->m_data);
        }
    }
}

template <typename T>
void BST_Tree<T>::InOrderTraversal(void(*visit)(T data))
{
    InOrderTraversal(m_root, visit);
}

template <typename T>
void BST_Tree<T>::InOrderTraversal(void(*visit)(T data), BST_Node<T> *node)
{
    if(node)
    {
        InOrderTraversal(node->m_left, visit);
        visit(node->mdata);
        InOrderTraversal(node->m_right, visit);
    }
}

template <typename T>
void BST_Tree<T>::PreOrderTraversal(void(*visit)(T data))
{
    PreOrderTraversal(m_root, visit);
}

template <typename T>
void BST_Tree<T>::PreOrderTraversal(void(*visit)(T data), BST_Node<T> *node)
{
    if(node)
    {
        visit(node->m_data);
        PreOrderTraversal(node->m_left, visit);
        PreOrderTraversal(node->m_right, visit);
    }
}

template <typename T>
void BST_Tree<T>::PostOrderTraversal(void(*visit)(T data))
{
    PostOrderTraversal(m_root, visit);
}

template <typename T>
void BST_Tree<T>::PostOrderTraversal(void(*visit)(T data), BST_Node<T> *node)
{
    if(node)
    {
        PostOrderTraversal(node->m_left, visit);
        PostOrderTraversal(node->m_right, visit);
        visit(node->m_data);
    }
}

template <typename T>
int BST_Tree<T>::Height()
{
    return Height(m_root);
}

template <typename T>
int BST_Tree<T>::Height(BST_Node<T> *node)
{
    int height = 0;
    if(node)
    {
        int left_height = Height(node->m_left);
        int right_height = Height(node->m_right);

        if(left_height > right_height)
            height = left_height + 1;
        else
            height = right_height + 1;
    }
    return height;
}
