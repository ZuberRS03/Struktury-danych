#ifndef BSTTREE_H
#define BSTTREE_H

#include <stdexcept>
#include <utility>

class BSTTree {
private:
    struct Node {
        int value;
        int priority;
        Node* left;
        Node* right;
        Node(int v, int p) : value(v), priority(p), left(nullptr), right(nullptr) {}
    };
    Node* root;
    int treeSize;

    Node* insert(Node* node, int value, int priority);
    Node* extractMax(Node*& node);
    Node* findMax(Node* node) const;
    Node* remove(Node* node, int value);
    void clear(Node* node);

public:
    BSTTree();
    ~BSTTree();
    void insert(int value, int priority);
    std::pair<int, int> extractMax();
    std::pair<int, int> findMax() const;
    void modifyKey(int value, int newPriority);
    int returnSize() const;
};

#endif