#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <stdexcept>

template<typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoubleLinkedList();

    ~DoubleLinkedList();

    void addFront(T data);

    void addBack(T data);

    void addAt(T data, int index);

    void removeFront();

    void removeBack();

    void printForward() const;

    void printBackward() const;

    void clear();
};

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {

}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    clear();
}

template<typename T>
void DoubleLinkedList<T>::addFront(T data) {
    // Implementacja metody addFront
    void addFront(T data) {
        Node<T>* newNode = new Node<T>(data, nullptr, head);
        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        size++;
    }
}

template<typename T>
void DoubleLinkedList<T>::addBack(T data) {
    // Implementacja metody addBack
    void addBack(T data) {
        Node<T>* newNode = new Node<T>(data, tail, nullptr);
        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        size++;
    }
}

template<typename T>
void DoubleLinkedList<T>::addAt(T data, int index) {
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
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }
        Node<T>* newNode = new Node<T>(data, temp, temp->next);
        temp->next->prev = newNode;
        temp->next = newNode;
        size++;
    }
}

template<typename T>
void DoubleLinkedList<T>::removeFront() {
    // Implementacja metody removeFront
    void removeFront() {
        if (head == nullptr) return;
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }
}

template<typename T>
void DoubleLinkedList<T>::removeBack() {
    // Implementacja metody removeBack
    void removeBack() {
        if (tail == nullptr) return;
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
    }
}

template<typename T>
void DoubleLinkedList<T>::printForward() const {
    // Implementacja metody printForward
    void printForward() const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << "\n";
    }
}

template<typename T>
void DoubleLinkedList<T>::printBackward() const {
    // Implementacja metody printBackward
    void printBackward() const {
        Node<T>* temp = tail;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->prev;
        }
        std::cout << "\n";
    }
}

template<typename T>
void DoubleLinkedList<T>::clear() {
    // Implementacja metody clear
    void clear() {
        while (head != nullptr) {
            removeFront();
        }
        size = 0;
    }
}

#endif // DOUBLELINKEDLIST_H