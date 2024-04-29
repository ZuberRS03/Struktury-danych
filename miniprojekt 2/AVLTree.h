#ifndef AVLTREE_H
#define AVLTREE_H

class Node {
public:
    int key;
    Node *left;
    Node *right;
    int height;
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    Node* insert(Node* node, int key);
    Node* deleteNode(Node* node, int key);
    Node* minValueNode(Node* node);
    int height(Node* N);
    int max(int a, int b);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    int getBalance(Node* N);

public:
    AVLTree();
    ~AVLTree();
    void insert(int key);
    void remove(int key);
    int findMax();
    bool isEmpty();
};

#endif