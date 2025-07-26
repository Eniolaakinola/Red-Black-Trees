/*
Name: Eniola Akinola
Class: CPT_S 223 Advanced Data Structures
Date: 7/25/2025
Description: Implementation of Red Black Tree
*/
#include "RedBlackTree.h"

int main() {
    RedBlackTree<int> rbt;

    // Insert values
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);

    // Print tree structure
    cout << "Initial Red-Black Tree:" << endl;
    rbt.printTree();

    // Inorder traversal (should be sorted)
    cout << "\nInorder traversal: ";
    rbt.inorder();  // Output: 10 15 20 30

    // Search for values
    cout << "\nSearching for 15: ";
    cout << (rbt.search(15) ? "Found" : "Not Found") << endl;

    cout << "Searching for 25: ";
    cout << (rbt.search(25) ? "Found" : "Not Found") << endl;

    // Remove a value
    cout << "\nRemoving 20 from the tree..." << endl;
    rbt.remove(20);

    // Print tree after deletion
    cout << "\nRed-Black Tree after deletion:" << endl;
    rbt.printTree();

    // Final Inorder traversal
    cout << "\nFinal Inorder traversal: ";
    rbt.inorder();

    return 0;
}

