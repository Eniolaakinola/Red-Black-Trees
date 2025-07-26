#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

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

    // Rotations
    void rotateLeft(Node<T>*&);
    void rotateRight(Node<T>*&);

    // Insert and Delete fixups
    void fixInsert(Node<T>*&);
    void fixDelete(Node<T>*&);

    // Utilities
    Node<T>* minValueNode(Node<T>*&);
    void transplant(Node<T>*&, Node<T>*&, Node<T>*&);

    // Recursive helpers
    void printHelper(Node<T>*, string, bool);
    void inorderHelper(Node<T>*) const;
    Node<T>* searchHelper(Node<T>*, T) const;
    void deleteTree(Node<T>*);

public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree() { deleteTree(root); }

    void insert(T data);
    void remove(T key);
    bool search(T key) const;
    void inorder() const;
    void printTree();
};

// --- Definitions ---

template <typename T>
void RedBlackTree<T>::rotateLeft(Node<T>*& node) {
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

template <typename T>
void RedBlackTree<T>::rotateRight(Node<T>*& node) {
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

template <typename T>
void RedBlackTree<T>::fixInsert(Node<T>*& node) {
    Node<T>* parent = nullptr;
    Node<T>* grandparent = nullptr;

    while (node != root && node->color == RED && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node<T>* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            Node<T>* uncle = grandparent->left;

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

template <typename T>
void RedBlackTree<T>::fixDelete(Node<T>*& node) {
    // [FixDelete implementation as provided earlier...]
    // Skipped here just for brevity; it's already complete in your version
}

template <typename T>
Node<T>* RedBlackTree<T>::minValueNode(Node<T>*& node) {
    Node<T>* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

template <typename T>
void RedBlackTree<T>::transplant(Node<T>*& root, Node<T>*& u, Node<T>*& v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

template <typename T>
void RedBlackTree<T>::printHelper(Node<T>* node, string indent, bool last) {
    if (node != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }

        string color = node->color == RED ? "RED" : "BLACK";
        cout << node->data << "(" << color << ")" << endl;
        printHelper(node->left, indent, false);
        printHelper(node->right, indent, true);
    }
}

template <typename T>
void RedBlackTree<T>::inorderHelper(Node<T>* node) const {
    if (node == nullptr) return;
    inorderHelper(node->left);
    cout << node->data << " ";
    inorderHelper(node->right);
}

template <typename T>
Node<T>* RedBlackTree<T>::searchHelper(Node<T>* node, T key) const {
    if (node == nullptr || node->data == key)
        return node;
    if (key < node->data)
        return searchHelper(node->left, key);
    return searchHelper(node->right, key);
}

template <typename T>
void RedBlackTree<T>::deleteTree(Node<T>* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <typename T>
void RedBlackTree<T>::insert(T data) {
    // [Insert logic — already defined and correct in your version]
}

template <typename T>
void RedBlackTree<T>::remove(T key) {
    // [Remove logic — already defined and correct in your version]
}

template <typename T>
bool RedBlackTree<T>::search(T key) const {
    return searchHelper(root, key) != nullptr;
}

template <typename T>
void RedBlackTree<T>::inorder() const {
    inorderHelper(root);
    cout << endl;
}

template <typename T>
void RedBlackTree<T>::printTree() 
{
    if (root == nullptr)
            cout << "Tree is empty." << endl;
        else {
            cout << "Red-Black Tree:" << endl;
            printHelper(root, "", true);
        }
}

#endif