#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template <typename T>
class Node {
public:
    T data; // Dane przechowywane w węźle
    Node<T>* next; // Wskaźnik na następny węzeł w liście

    // Konstruktor inicjalizujący węzeł z danymi i opcjonalnie z następnym węzłem
    Node(T data, Node<T>* next = nullptr) : data(data), next(next) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head; // Głowa listy, czyli pierwszy element

public:
    // Konstruktor inicjalizujący listę jako pustą
    LinkedList() : head(nullptr) {}

    // Destruktor zwalniający pamięć
    ~LinkedList() {
        clear();
    }

    // Metoda dodająca element na początku listy
    void addFront(T data) {
        Node<T>* newNode = new Node<T>(data, head);
        head = newNode;
    }

    // Metoda usuwająca element z początku listy
    void removeFront() {
        if (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Metoda wyświetlająca wszystkie elementy listy
    void print() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Metoda czyszcząca listę
    void clear() {
        while (head != nullptr) {
            removeFront();
        }
    }
};

#endif // LINKEDLIST_H