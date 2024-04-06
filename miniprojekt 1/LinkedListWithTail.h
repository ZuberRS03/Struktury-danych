#ifndef LINKEDLISTWITHTAIL_H
#define LINKEDLISTWITHTAIL_H

#include "Node.h"
#include <iostream>

template <typename T>
class LinkedListWithTail {
private:
    Node<T>* head; // Głowa listy, czyli pierwszy element
    Node<T>* tail; // Ogon listy, czyli ostatni element
    int size;

public:
    // Konstruktor inicjalizujący listę jako pustą
    LinkedListWithTail() : head(nullptr), tail(nullptr), size(0) {}

    // Destruktor zwalniający pamięć
    ~LinkedListWithTail();

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

    // Metoda wyświetlająca wszystkie elementy listy
    void print();

    // Metoda czyszcząca listę
    void clear();
};

template<typename T>
LinkedListWithTail<T>::~LinkedListWithTail() {
    clear();
}

template<typename T>
void LinkedListWithTail<T>::addFront(T data) {
    Node<T>* newNode = new Node<T>(data);
    if(head == nullptr) { // Jeśli lista jest pusta, nowy węzeł jest również ogonem
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

template<typename T>
void LinkedListWithTail<T>::addEnd(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = tail->next;
    }
    size++;
}

template<typename T>
void LinkedListWithTail<T>::addAt(T data, int index) {
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
int LinkedListWithTail<T>::find(T element) {
    Node<T>* temp = head;
    int index = 0;
    while (temp != nullptr) {
        if (temp->data == element) {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}

template<typename T>
void LinkedListWithTail<T>::removeFront() {
    if (head == nullptr) return;
    Node<T>* temp = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    size--;
}

template<typename T>
void LinkedListWithTail<T>::print() {
    Node<T>* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

template<typename T>
void LinkedListWithTail<T>::clear() {
    while (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}



#endif // LINKEDLISTWITHTAIL_H