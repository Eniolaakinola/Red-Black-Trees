/*
Name: Eniola Akinola
Date: 7/25/25
Topic: Red-Black Trees
Description: in CPT_s 233  we discussed about different advanced Data structure. Below is an implemenation of Red-Black Trees
*/

#include "RedBlackTree.h"

int main() {
    RedBlackTree<int> rbt;

    // Insert nodes to shape the expected tree
    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(2);
    rbt.insert(6);
    rbt.insert(18);
    rbt.insert(10);
    rbt.insert(8);
    rbt.insert(11);
    rbt.insert(22);
    rbt.insert(26);

    // Display initial Red-Black Tree
    cout << "Red-Black Tree:" << endl;
    rbt.printTree();

    // First Deletion
    cout << "\nAfter deleting 18:" << endl;
    rbt.remove(18);
    rbt.printTree();

    // Second Deletion
    cout << "\nAfter deleting 11:" << endl;
    rbt.remove(11);
    rbt.printTree();

    // Third Deletion
    cout << "\nAfter deleting 3:" << endl;
    rbt.remove(3);
    rbt.printTree();

    return 0;
}