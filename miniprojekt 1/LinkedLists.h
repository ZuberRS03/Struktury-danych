#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

template <typename T>
class LinkedList {
private:
    Node<T>* head; // Głowa listy, czyli pierwszy element
    int size;

public:
    // Konstruktor inicjalizujący listę jako pustą
    LinkedList() : head(nullptr), size(0) {}

    // Destruktor zwalniający pamięć
    ~LinkedList();

    // Metoda dodająca element na początku listy
    void addFront(T data);

    // Metoda dodająca element na końcu listy
    void addEnd(T data);

    // Metoda dodająca element na podanym indeksie
    void addAt(T data, int index);

    // Metoda usuwająca element z początku listy
    void removeFront();

    // Metoda wyświetlająca wszystkie elementy listy
    void print();

    // Metoda czyszcząca listę
    void clear();
};

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void LinkedList<T>::addFront(T data) {
    Node<T>* newNode = new Node<T>(data, head);
    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
void LinkedList<T>::addEnd(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    size++;
}

template<typename T>
void LinkedList<T>::addAt(T data, int index) {
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
        temp->next = newNode;
        size++;
    }
}

template<typename T>
void LinkedList<T>::removeFront() {
    if (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
}

template<typename T>
void LinkedList<T>::print() {
    Node<T>* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

template<typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        removeFront();
    }
}


#endif // LINKEDLIST_H