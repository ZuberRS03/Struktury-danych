#ifndef NODE_H
#define NODE_H

template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev; // Dodane dla wsparcia listy dwukierunkowej, dla listy jednokierunkowej pozostaje nie używane

    Node(T data, Node* prev = nullptr, Node* next = nullptr) : data(data), prev(prev), next(next) {}
};

#endif // NODE_H