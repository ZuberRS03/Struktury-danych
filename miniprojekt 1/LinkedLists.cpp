#include "LinkedLists.h"

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void LinkedList<T>::addFront(T data) {
    Node<T>* newNode = new Node<T>(data, head); //tworzymy nowy węzeł
    newNode->next = head; //ustawiamy wskaźnik na następny węzeł na wskaźnik na głowę
    head = newNode; //ustawiamy wskaźnik na głowę na nowy węzeł
    size++; //zwiększamy licznik elementów
}

template<typename T>
void LinkedList<T>::addEnd(T data) {
    Node<T>* newNode = new Node<T>(data); //tworzymy nowy węzeł
    if (head == nullptr) { //jeżeli wskaźnik na głowę jest równy nullptr
        head = newNode; //ustawiamy wskaźnik na głowę na nowy węzeł
    } else {
        Node<T>* temp = head; //tworzymy wskaźnik na głowę
        while (temp->next != nullptr) { //dopóki wskaźnik na następny węzeł nie jest równy nullptr
            temp = temp->next; //przesuwamy wskaźnik na następny węzeł
        }
        temp->next = newNode;  //ustawiamy wskaźnik na następny węzeł na nowy węzeł
    }
    size++; //zwiększamy licznik elementów
}

template<typename T>
void LinkedList<T>::addAt(T data, int index) {
    if (index < 0 || index > size) { //jeżeli indeks jest mniejszy od 0 lub większy od liczby elementów w tablicy
        throw std::out_of_range("Niepoprawny indeks");
    }
    if (index == 0) { //jeżeli indeks jest równy 0
        addFront(data); //dodajemy nowy element na początku listy
    } else if (index == size) { //jeżeli indeks jest równy liczbie elementów w tablicy
        addEnd(data); //dodajemy nowy element na końcu listy
    } else { //jeżeli indeks jest większy od 0 i mniejszy od liczby elementów w tablicy
        Node<T>* newNode = new Node<T>(data); //tworzymy nowy węzeł
        Node<T>* temp = head; //tworzymy wskaźnik na głowę
        for (int i = 0; i < index - 1; i++) { //przesuwamy wskaźnik na węzeł o indeksie o 1
            temp = temp->next; //przesuwamy wskaźnik na następny węzeł
        }
        newNode->next = temp->next; //ustawiamy wskaźnik na następny węzeł na następny węzeł
        temp->next = newNode; //ustawiamy wskaźnik na następny węzeł na nowy węzeł
        size++; //zwiększamy licznik elementów
    }
}

template<typename T>
int LinkedList<T>::find(T element) {
    Node<T>* temp = head; //tworzymy wskaźnik na głowę
    int index = 0; //tworzymy zmienną przechowującą indeks
    while (temp != nullptr) {  //dopóki wskaźnik na węzeł nie jest równy nullptr
        if (temp->data == element) { //jeżeli element węzła jest równy szukanemu elementowi
            return index; //zwracamy indeks
        }
        temp = temp->next; //przesuwamy wskaźnik na następny węzeł
        index++; //zwiększamy indeks
    }
    return -1; //jeżeli nie znaleziono elementu zwracamy -1
}

template<typename T>
void LinkedList<T>::removeFront() {
    if (head != nullptr) { //jeżeli wskaźnik na głowę nie jest równy nullptr
        Node<T>* temp = head; //tworzymy wskaźnik na głowę
        head = head->next; //ustawiamy wskaźnik na głowę na następny węzeł
        delete temp; //zwalniamy pamięć zajmowaną przez wskaźnik na węzeł
        size--; //zmniejszamy licznik elementów
    }
}

template<typename T>
void LinkedList<T>::removeEnd() {
    if (head == nullptr) { //jeżeli wskaźnik na głowę jest równy nullptr
        throw std::out_of_range("Lista jest pusta");
    }
    if (head->next == nullptr) { //jeżeli wskaźnik na następny węzeł jest równy nullptr
        delete head;  //zwalniamy pamięć zajmowaną przez wskaźnik na głowę
        head = nullptr; //ustawiamy wskaźnik na głowę na nullptr
    } else { //jeżeli wskaźnik na następny węzeł nie jest równy nullptr
        Node<T>* temp = head; //tworzymy wskaźnik na głowę
        while (temp->next->next != nullptr) { //dopóki wskaźnik na następny węzeł nie jest równy nullptr
            temp = temp->next; //przesuwamy wskaźnik na następny węzeł
        }
        delete temp->next; //zwalniamy pamięć zajmowaną przez wskaźnik na następny węzeł
        temp->next = nullptr; //ustawiamy wskaźnik na następny węzeł na nullptr
    }
    size--; //zmniejszamy licznik elementów
}

template<typename T>
void LinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= size) { //jeżeli indeks jest mniejszy od 0 lub większy od liczby elementów w tablicy
        throw std::out_of_range("Niepoprawny indeks");
    }
    if (index == 0) { //jeżeli indeks jest równy 0
        removeFront(); //usuwamy pierwszy element
    } else if (index == size - 1) { //jeżeli indeks jest równy liczbie elementów w tablicy - 1
        removeEnd(); //usuwamy ostatni element
    } else { //jeżeli indeks jest większy od 0 i mniejszy od liczby elementów w tablicy - 1
        Node<T>* temp = head; //tworzymy wskaźnik na głowę
        for (int i = 0; i < index - 1; i++) { //przesuwamy wskaźnik na węzeł o indeksie o 1
            temp = temp->next; //przesuwamy wskaźnik na następny węzeł
        }
        Node<T>* toDelete = temp->next; //tworzymy wskaźnik na węzeł do usunięcia
        temp->next = temp->next->next; //ustawiamy wskaźnik na następny węzeł na następny węzeł
        delete toDelete; //zwalniamy pamięć zajmowaną przez wskaźnik na węzeł do usunięcia
        size--; //zmniejszamy licznik elementów
    }
}

template<typename T>
void LinkedList<T>::print() {
    Node<T>* temp = head; //tworzymy wskaźnik na głowę
    while (temp != nullptr) { //dopóki wskaźnik na węzeł nie jest równy nullptr
        std::cout << temp->data << " "; //wyświetlamy element węzła
        temp = temp->next; //przesuwamy wskaźnik na następny węzeł
    }
    std::cout << std::endl;
}

template<typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) { //dopóki wskaźnik na głowę nie jest równy nullptr
        removeFront(); //usuwamy pierwszy element
    }
}

template class LinkedList<int>; //definicja klasy LinkedList dla typu int
