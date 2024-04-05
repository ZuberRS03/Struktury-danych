#ifndef LINKEDLISTWITHTAIL_H
#define LINKEDLISTWITHTAIL_H

#include "Node.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedListWithTail {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedListWithTail();

    ~LinkedListWithTail();

    void addFront(T data);

    void addBack(T data);

    void addAt(T data, int index);

    void removeFront();

    void print();

    void clear();
};

template<typename T>
LinkedListWithTail<T>::LinkedListWithTail() : head(nullptr), tail(nullptr), size(0) {

}

template<typename T>
LinkedListWithTail<T>::~LinkedListWithTail() {
    clear();
}

template<typename T>
void LinkedListWithTail<T>::addFront(T data) {
    // Implementacja metody addFront
     void addFront(T data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) {
            tail = head;
        }
        size++;
    }
}

template<typename T>
void LinkedListWithTail<T>::addBack(T data) {
    // Implementacja metody addBack
    void addBack(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
}

template<typename T>
void LinkedListWithTail<T>::addAt(T data, int index) {
    // Implementacja metody addAt
    void addAt(T data, int index) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            addFront(data);
            return;
        }
        if (index == size) {
            addBack(data);
            return;
        }
        Node<T>* newNode = new Node<T>(data);
        Node<T>* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
}

template<typename T>
void LinkedListWithTail<T>::removeFront() {
    // Implementacja metody removeFront
    void removeFront() {
        if (head == nullptr) return;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
        size--;
    }
}

template<typename T>
void LinkedListWithTail<T>::print() {
    // Implementacja metody print
    void print() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << "\n";
    }
}

template<typename T>
void LinkedListWithTail<T>::clear() {
    // Implementacja metody clear
    void clear() {
        while (head != nullptr) {
            removeFront();
        }
        size = 0;
    }

}

#endif // LINKEDLISTWITHTAIL_H