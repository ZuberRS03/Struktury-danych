#ifndef NODE_H
#define NODE_H

template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev; // Używane tylko przez DoubleLinkedList

    // Konstruktor uniwersalny
    Node(T data, Node* prev = nullptr, Node* next = nullptr) : data(data), prev(prev), next(next) {}
};

#endif // NODE_H