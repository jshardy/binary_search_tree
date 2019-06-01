#include <iostream>
#include "BST_Tree.h"

using std::cin;
using std::cout;
using std::endl;


template <typename T>
void display(T data);

int main(int argc, char **argv)
{
    BST_Tree<int> tree;

    tree.Insert(50);
    tree.Insert(45);
    tree.Insert(30);
    tree.Insert(35);
    tree.Insert(46);
    tree.Insert(48);
    tree.Insert(65);
    tree.Insert(60);
    tree.Insert(73);

    tree.BreadthFirst(display);
    cout << endl;

    return 0;
}

template <typename T>
void display(T data)
{
    cout << data << ", ";
}
