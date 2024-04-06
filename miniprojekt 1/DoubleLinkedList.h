#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "Node.h"
#include <iostream>

template<typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoubleLinkedList();

    // Metoda dodająca element na początku listy
    void addFront(T data);

    // Metoda dodająca element na końcu listy
    void addEnd(T data);

    // Metoda dodająca element na podanym indeksie
    void addAt(T data, int index);

    // Metoda wyszukująca element w liście
    int find(T element);

    // Metoda usuwająca element z początku listy
    void removeFront();

    // Metoda usuwająca element z końca listy
    void removeEnd();

    // Metoda wyświetlająca wszystkie elementy listy
    void print() const;

    // Metoda czyszcząca listę
    void clear();
};

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    clear();
}

template<typename T>
void DoubleLinkedList<T>::addFront(T data) {

    Node<T>* newNode = new Node<T>(data, nullptr, head);
    if (head != nullptr) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
    size++;
}

template<typename T>
void DoubleLinkedList<T>::addEnd(T data) {
    Node<T>* newNode = new Node<T>(data, tail, nullptr);
    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
    size++;
}

template<typename T>
void DoubleLinkedList<T>::removeFront() {
    if (head != nullptr) {
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
void DoubleLinkedList<T>::removeEnd() {
    if (tail != nullptr) {
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
void DoubleLinkedList<T>::print() const {
    Node<T>* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

template<typename T>
void DoubleLinkedList<T>::clear() {
    while (head != nullptr) {
        removeFront();
    }
}

template<typename T>
void DoubleLinkedList<T>::addAt(T data, int index) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Niepoprawny indeks");
    }
    if (index == 0) {
        addFront(data);
    } else if (index == size) {
        addEnd(data);
    } else {
        Node<T>* newNode = new Node<T>(data);
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        size++;
    }
}

template<typename T>
int DoubleLinkedList<T>::find(T element) {
    Node<T>* temp = head;
    int index = 0;
    while (temp != nullptr) {
        if (temp->data == element) {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1; //jeden jesli element nie zostal znaleziony
}

#endif // DOUBLELINKEDLIST_H