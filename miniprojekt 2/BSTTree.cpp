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
    Node* newNode = new Node(value, priority);
    if (!root) {
        root = newNode;
        treeSize++;
        return;
    }

    Node* parent = nullptr;
    Node* current = root;
    while (current) {
        parent = current;
        if (priority < current->priority) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (priority < parent->priority) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

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

BSTTree::Node* BSTTree::remove(Node* root, int value) {
    Node* parent = nullptr;
    Node* current = root;
    while (current && current->value != value) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (!current) return root; // Nie znaleziono wartości

    // Przypadek 1: Usuwany węzeł nie ma potomków (węzeł liści)
    if (!current->left && !current->right) {
        if (current != root) {
            if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }
        delete current;
        treeSize--;
    }
    // Przypadek 2: Usuwany węzeł ma dwa potomki
    else if (current->left && current->right) {
        Node* successor = current->right;
        Node* successorParent = current;

        while (successor->left) {
            successorParent = successor;
            successor = successor->left;
        }

        current->value = successor->value;
        current->priority = successor->priority;

        if (successorParent != current) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }

        delete successor;
        treeSize--;
    }
    // Przypadek 3: Usuwany węzeł ma jednego potomka
    else {
        Node* child = (current->left) ? current->left : current->right;

        if (current != root) {
            if (current == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            root = child;
        }

        delete current;
        treeSize--;
    }

    return root;
}

int BSTTree::returnSize() const {
    return treeSize;
}

void BSTTree::clear() {
    clear(root);
    root = nullptr;
    treeSize = 0;
}

void BSTTree::print() const {
    print(root);
    std::cout << std::endl;
}

void BSTTree::print(Node* node) const {
    if (node) {
        print(node->left);
        std::cout << node->value << " " << node->priority << std::endl;
        print(node->right);
    }
}