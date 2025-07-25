/*
Name: Eniola Akinola
Date: 7/25/25
Topic: Red-Black Trees
Description: in CPT_s 233  we discussed about different advanced Data structure. Below is an implemenation of Red-Black Trees
*/

#include "RedBlackTree.h"

int main()
{
    RedBlackTree<int> rbtree;

    // Inserting values into Red-Black Tree
    rbtree.insert(7);
    rbtree.insert(3);
    rbtree.insert(18);
    rbtree.insert(10);
    rbtree.insert(22);
    rbtree.insert(8);
    rbtree.insert(11);
    rbtree.insert(26);
    rbtree.insert(2);
    rbtree.insert(6);

    // Printing Red-Black Tree
    rbtree.printTree();

    // Deleting nodes from Red-Black Tree

    cout << "After deleting 18:" << endl;
    rbtree.remove(18);
    rbtree.printTree();

    cout << "After deleting 11:" << endl;
    rbtree.remove(11);
    rbtree.printTree();

    cout << "After deleting 3:" << endl;
    rbtree.remove(3);
    rbtree.printTree();


    return 0;
}