#pragma once

template <typename T>
class BST_Tree;

template <typename T>
class BST_Node
{
public:
    BST_Node(T data);
    BST_Node(T data, BST_Node<T> *left, BST_Node<T> *right);

    BST_Node(const BST_Node<T> &copy);
    BST_Node<T> &operator=(const BST_Node<T> &copy);

    //~BST_Node() = default;

    T &GetData();

protected:
    T m_data;

    BST_Node<T> *m_left;
    BST_Node<T> *m_right;
    template <typename X> friend class BST_Tree;
};

template <typename T>
BST_Node<T>::BST_Node(T data)
    : m_data(data), m_left(NULL), m_right(NULL)
{

}

template <typename T>
BST_Node<T>::BST_Node(T data, BST_Node<T> *left, BST_Node<T> *right)
    : m_data(data), m_left(left), m_right(right)
{

}

//Don't copy left and right pointers
template <typename T>
BST_Node<T>::BST_Node(const BST_Node<T> &copy)
    : m_data(copy.data), m_left(NULL), m_right(NULL)
{

}

//Don't copy left and right pointers
template <typename T>
BST_Node<T> &BST_Node<T>::operator=(const BST_Node<T> &copy)
{
    if(this != &copy)
    {
        m_data = copy.m_data;
        m_left = NULL;
        m_right = NULL;
    }
    return *this;
}

template <typename T>
T &BST_Node<T>::GetData()
{
    return m_data;
}
