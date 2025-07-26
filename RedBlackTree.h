#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <cstring>		// strcmp
#include <vector>
#include <initializer_list>
#include <queue>

using namespace std;

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

template <typename T>
class Node {
public:
    T data;
    Color color;
    Node *left, *right, *parent;

    Node(T data)
        : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RedBlackTree {
private:
    Node<T>* root;

    // Helper function for left rotate
    void rotateLeft(Node<T>*& node) {
        Node<T>* rightChild = node->right;
        node->right = rightChild->left;
        if (node->right != nullptr)
            node->right->parent = node;

        rightChild->parent = node->parent;
        if (node->parent == nullptr)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    // Helper function for right rotate
    void rotateRight(Node<T>*& node) {
        Node<T>* leftChild = node->left;
        node->left = leftChild->right;
        if (node->left != nullptr)
            node->left->parent = node;

        leftChild->parent = node->parent;
        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    // Fix tree after insertion
    void fixInsert(Node<T>*& node) {
        Node<T>* parent = nullptr;
        Node<T>* grandparent = nullptr;

        while (node != root && node->color == RED && node->parent->color == RED) {
            parent = node->parent;
            grandparent = parent->parent;

            // Parent is left child
            if (parent == grandparent->left) {
                Node<T>* uncle = grandparent->right;

                // Case 1: Uncle is red
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    // Case 2: node is right child
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    // Case 3: node is left child
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                Node<T>* uncle = grandparent->left;

                // Mirror cases
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
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

        root->color = BLACK;
    }

    // Recursive helper for printing
    void printHelper(Node<T>* root, string indent, bool last) {
        if (root != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }

            string color = root->color == RED ? "RED" : "BLACK";
            cout << root->data << "(" << color << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    // Helper for inorder traversal
    void inorderHelper(Node<T>* node) const {
        if (node == nullptr) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

    // Recursive helper for search
    Node<T>* searchHelper(Node<T>* node, T key) const {
        if (node == nullptr || node->data == key)
            return node;
        if (key < node->data)
            return searchHelper(node->left, key);
        return searchHelper(node->right, key);
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (root == nullptr) {
            newNode->color = BLACK;
            root = newNode;
        } else {
            Node<T>* temp = root;
            Node<T>* parent = nullptr;
            while (temp != nullptr) {
                parent = temp;
                if (data < temp->data)
                    temp = temp->left;
                else
                    temp = temp->right;
            }
            newNode->parent = parent;
            if (data < parent->data)
                parent->left = newNode;
            else
                parent->right = newNode;

            fixInsert(newNode);
        }
    }

    // Public function to print tree structure
    void printTree() {
        if (root)
            printHelper(root, "", true);
    }

    // Public function to perform inorder traversal
    void inorder() const {
        inorderHelper(root);
        cout << endl;
    }

    // Public function to search a value
    bool search(T key) const {
        return searchHelper(root, key) != nullptr;
    }
};

#endif
