#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <cstring>		// strcmp
#include <vector>
#include <initializer_list>
#include <queue>

using namespace std;

// Define the two possible node colors
enum Color { RED, BLACK };

// Templated Red-Black Tree class
template <typename T>
class RedBlackTree {
private:
    // Internal Node structure
    struct Node {
        T data;                 // Node value
        Color color;            // Node color (RED or BLACK)
        Node* parent;           // Pointer to parent node
        Node* left;             // Pointer to left child
        Node* right;            // Pointer to right child

        // Constructor for a new node (defaults to RED)
        Node(T value)
            : data(value), color(RED), parent(nullptr),
              left(nullptr), right(nullptr) {}
    };

    Node* root;  // Root of the tree

    // Rotate left around a node
    void rotateLeft(Node*& node) {
        Node* child = node->right;
        node->right = child->left;
        if (child->left != nullptr)
            child->left->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->left = node;
        node->parent = child;
    }

    // Rotate right around a node
    void rotateRight(Node*& node) {
        Node* child = node->left;
        node->left = child->right;
        if (child->right != nullptr)
            child->right->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->right)
            node->parent->right = child;
        else
            node->parent->left = child;
        child->right = node;
        node->parent = child;
    }

    // Fix violations after insert
    void fixInsert(Node*& node) {
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while (node != root && node->parent->color == RED) {
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;

                // Case 1: Uncle is red (recoloring)
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                }
                else {
                    // Case 2: Node is right child (left rotate)
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    // Case 3: Node is left child (right rotate)
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            else {
                // Mirror image of the above code
                Node* uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                }
                else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        root->color = BLACK; // Root is always black
    }

    // Fix double-black violations after deletion
    void fixDelete(Node*& node) {
        while (node != root && (node == nullptr || node->color == BLACK)) {
            if (node == node->parent->left) {
                Node* sibling = node->parent->right;

                // Case 1: Sibling is red
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateLeft(node->parent);
                    sibling = node->parent->right;
                }

                // Case 2: Sibling’s children are black
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                }
                else {
                    // Case 3: Sibling's right child is black
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        if (sibling->left != nullptr)
                            sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = node->parent->right;
                    }

                    // Case 4: Sibling’s right child is red
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    rotateLeft(node->parent);
                    node = root;
                }
            }
            else {
                // Mirror image of the above logic
                Node* sibling = node->parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }

                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                }
                else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        if (sibling->right != nullptr)
                            sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }

        if (node != nullptr)
            node->color = BLACK;
    }

    // Returns the node with the minimum key value
    Node* minValueNode(Node*& node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Replaces one subtree with another
    void transplant(Node*& root, Node*& u, Node*& v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v != nullptr)
            v->parent = u->parent;
    }

    // Recursively prints the tree structure
    void printHelper(Node* root, string indent, bool last) {
        if (root != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = (root->color == RED) ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    // Deletes the entire tree
    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    // Constructor initializes an empty tree
    RedBlackTree() : root(nullptr) {}

    // Destructor deletes the tree
    ~RedBlackTree() { deleteTree(root); }

    // Inserts a new key into the tree
    void insert(T key) {
        Node* node = new Node(key);
        Node* parent = nullptr;
        Node* current = root;

        // Regular BST insert
        while (current != nullptr) {
            parent = current;
            if (node->data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        node->parent = parent;

        if (parent == nullptr)
            root = node;
        else if (node->data < parent->data)
            parent->left = node;
        else
            parent->right = node;

        // Fix Red-Black Tree properties
        fixInsert(node);
    }

    // Removes a key from the tree
    void remove(T key) {
        Node* node = root;
        Node* z = nullptr;
        Node* x = nullptr;
        Node* y = nullptr;

        // Search for the node to delete
        while (node != nullptr) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key)
                node = node->right;
            else
                node = node->left;
        }

        if (z == nullptr) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        Color yOriginalColor = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(root, z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            transplant(root, z, z->left);
        }
        else {
            y = minValueNode(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x != nullptr)
                    x->parent = y;
            } else {
                transplant(root, y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(root, z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (yOriginalColor == BLACK)
            fixDelete(x);
    }

    // Prints the Red-Black Tree
    void printTree() {
        if (root == nullptr)
            cout << "Tree is empty." << endl;
        else {
            cout << "Red-Black Tree:" << endl;
            printHelper(root, "", true);
        }
    }
};

#endif // REDBLACKTREE_H
