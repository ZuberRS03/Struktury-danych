#include "BSTTree.h"

BSTTree::BSTTree() : root(nullptr), treeSize(0) {}

BSTTree::~BSTTree() {
    clear(root);
}

void BSTTree::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void BSTTree::insert(int value, int priority) {
    root = insert(root, value, priority);
    treeSize++;
}

BSTTree::Node* BSTTree::insert(Node* node, int value, int priority) {
    if (!node) return new Node(value, priority);
    if (priority > node->priority) {
        Node* newNode = new Node(value, priority);
        newNode->left = node;  // Insert new node above the current node
        return newNode;
    } else if (priority < node->priority) {
        node->left = insert(node->left, value, priority);
    } else {
        node->right = insert(node->right, value, priority);
    }
    return node;
}

std::pair<int, int> BSTTree::extractMax() {
    if (!root) throw std::runtime_error("BST is empty");
    std::pair<int, int> max = {root->value, root->priority};
    Node* maxNode = extractMax(root);
    delete maxNode;
    treeSize--;
    return max;
}

BSTTree::Node* BSTTree::extractMax(Node*& node) {
    if (!node->right) {
        Node* temp = node;
        node = node->left;
        return temp;
    }
    return extractMax(node->right);
}

std::pair<int, int> BSTTree::findMax() const {
    Node* maxNode = findMax(root);
    if (!maxNode) throw std::runtime_error("BST is empty");
    return {maxNode->value, maxNode->priority};
}

BSTTree::Node* BSTTree::findMax(Node* node) const {
    while (node && node->right) node = node->right;
    return node;
}

void BSTTree::modifyKey(int value, int newPriority) {
    root = remove(root, value);
    insert(value, newPriority);
}

BSTTree::Node* BSTTree::remove(Node* node, int value) {
    if (!node) return nullptr;
    if (value < node->value)
        node->left = remove(node->left, value);
    else if (value > node->value)
        node->right = remove(node->right, value);
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            treeSize--;
            return temp;
        } else {
            Node* temp = findMax(node->left);
            node->value = temp->value;
            node->priority = temp->priority;
            node->left = remove(node->left, temp->value);
        }
    }
    return node;
}

int BSTTree::returnSize() const {
    return treeSize;
}