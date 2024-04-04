#ifndef LINKEDLISTWITHTAIL_H
#define LINKEDLISTWITHTAIL_H

#include <iostream>

template <typename T>
class Node {
public:
    T data; // Dane przechowywane w węźle
    Node<T>* next; // Wskaźnik na następny węzeł w liście

    Node(T data, Node<T>* next = nullptr) : data(data), next(next) {}
};

template <typename T>
class LinkedListWithTail {
private:
    Node<T>* head; // Głowa listy, czyli pierwszy element
    Node<T>* tail; // Ogon listy, czyli ostatni element

public:
    // Konstruktor inicjalizujący listę jako pustą
    LinkedListWithTail() : head(nullptr), tail(nullptr) {}

    // Destruktor zwalniający pamięć
    ~LinkedListWithTail() {
        clear();
    }

    // Metoda dodająca element na początku listy
    void addFront(T data) {
        Node<T>* newNode = new Node<T>(data, head);
        head = newNode;
        if(tail == nullptr) { // Jeśli lista była pusta, nowy węzeł jest również ogonem
            tail = head;
        }
    }

    // Metoda dodająca element na końcu listy
    void addBack(T data) {
        Node<T>* newNode = new Node<T>(data);
        if(tail == nullptr) { // Jeśli lista jest pusta
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Metoda usuwająca element z początku listy
    void removeFront() {
        if (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            if(head == nullptr) { // Jeśli usunięto ostatni element
                tail = nullptr;
            }
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

#endif // LINKEDLISTWITHTAIL_H