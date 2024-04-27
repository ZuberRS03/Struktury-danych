#include "DoubleLinkedList.h"

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    clear();
}

template<typename T>
void DoubleLinkedList<T>::addFront(T data) {

    Node<T>* newNode = new Node<T>(data, nullptr, head); //tworzymy nowy węzeł
    if (head != nullptr) { //jeżeli wskaźnik na głowę nie jest równy nullptr
        head->prev = newNode; //ustawiamy wskaźnik na poprzedni węzeł na nowy węzeł
    } else { //jeżeli wskaźnik na głowę jest równy nullptr
        tail = newNode; //ustawiamy wskaźnik na ogon na nowy węzeł
    }
    head = newNode; //ustawiamy wskaźnik na głowę na nowy węzeł
    size++; //zwiększamy licznik elementów
}

template<typename T>
void DoubleLinkedList<T>::addEnd(T data) {
    Node<T>* newNode = new Node<T>(data, tail, nullptr); //tworzymy nowy węzeł
    if (tail != nullptr) { //jeżeli wskaźnik na ogon nie jest równy nullptr
        tail->next = newNode; //ustawiamy wskaźnik na następny węzeł na nowy węzeł
    } else { //jeżeli wskaźnik na ogon jest równy nullptr
        head = newNode; //ustawiamy wskaźnik na głowę na nowy węzeł
    }
    tail = newNode; //ustawiamy wskaźnik na ogon na nowy węzeł
    size++; //zwiększamy licznik elementów
}

template<typename T>
void DoubleLinkedList<T>::removeFront() {
    if (head != nullptr) { //jeżeli wskaźnik na głowę nie jest równy nullptr
        Node<T>* temp = head; //tworzymy wskaźnik na głowę
        head = head->next; //ustawiamy wskaźnik na głowę na następny węzeł
        if (head != nullptr) { //jeżeli wskaźnik na głowę nie jest równy nullptr
            head->prev = nullptr; //ustawiamy wskaźnik na poprzedni węzeł na nullptr
        } else { //jeżeli wskaźnik na głowę jest równy nullptr
            tail = nullptr; //ustawiamy wskaźnik na ogon na nullptr
        }
        delete temp; //zwalniamy pamięć zajmowaną przez wskaźnik na głowę
        size--; //zmniejszamy licznik elementów
    }
}

template<typename T>
void DoubleLinkedList<T>::removeEnd() {
    if (tail != nullptr) { //jeżeli wskaźnik na ogon nie jest równy nullptr
        Node<T>* temp = tail; //tworzymy wskaźnik na ogon
        tail = tail->prev; //ustawiamy wskaźnik na ogon na poprzedni węzeł
        if (tail != nullptr) { //jeżeli wskaźnik na ogon nie jest równy nullptr
            tail->next = nullptr; //ustawiamy wskaźnik na następny węzeł na nullptr
        } else { //jeżeli wskaźnik na ogon jest równy nullptr
            head = nullptr; //ustawiamy wskaźnik na głowę na nullptr
        }
        delete temp; //zwalniamy pamięć zajmowaną przez wskaźnik na ogon
        size--; //zmniejszamy licznik elementów
    }
}

template<typename T>
void DoubleLinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= size) { //jeżeli indeks jest mniejszy od 0 lub większy od liczby elementów w tablicy
        throw std::out_of_range("Niepoprawny indeks");
    }
    if (index == 0) { //jeżeli indeks jest równy 0
        removeFront(); //usuwamy pierwszy element
    } else if (index == size - 1) { //jeżeli indeks jest równy liczbie elementów w tablicy - 1
        removeEnd(); //usuwamy ostatni element
    } else {
        Node<T>* temp = head; //tworzymy wskaźnik na głowę
        for (int i = 0; i < index; i++) { //przesuwamy wskaźnik na węzeł o indeksie o 1
            temp = temp->next;
        }
        temp->prev->next = temp->next; //ustawiamy wskaźnik na następny węzeł na następny węzeł
        temp->next->prev = temp->prev; //ustawiamy wskaźnik na poprzedni węzeł na poprzedni węzeł
        delete temp; //zwalniamy pamięć zajmowaną przez wskaźnik na węzeł
        size--; //zmniejszamy licznik elementów
    }
}

template<typename T>
void DoubleLinkedList<T>::print() const {
    Node<T>* temp = head; //tworzymy wskaźnik na głowę
    while (temp != nullptr) { //dopóki wskaźnik na węzeł nie jest równy nullptr
        std::cout << temp->data << " "; //wyświetlamy element węzła
        temp = temp->next; //przesuwamy wskaźnik na następny węzeł
    }
    std::cout << std::endl;
}

template<typename T>
void DoubleLinkedList<T>::clear() {
    while (head != nullptr) { //dopóki wskaźnik na głowę nie jest równy nullptr
        removeFront(); //usuwamy pierwszy element
    }
}

template<typename T>
void DoubleLinkedList<T>::addAt(T data, int index) {
    if (index < 0 || index > size) { //jeżeli indeks jest mniejszy od 0 lub większy od liczby elementów w tablicy
        throw std::out_of_range("Niepoprawny indeks");
    }
    if (index == 0) { //jeżeli indeks jest równy 0
        addFront(data); //dodajemy element na początek
    } else if (index == size) { //jeżeli indeks jest równy liczbie elementów w tablicy
        addEnd(data); //dodajemy element na koniec
    } else { //jeżeli indeks jest większy od 0 i mniejszy od liczby elementów w tablicy
        Node<T>* newNode = new Node<T>(data); //tworzymy nowy węzeł
        Node<T>* temp = head; //tworzymy wskaźnik na głowę
        for (int i = 0; i < index - 1; i++) { //przesuwamy wskaźnik na węzeł o indeksie o 1
            temp = temp->next; //przesuwamy wskaźnik na następny węzeł
        }
        newNode->next = temp->next; //ustawiamy wskaźnik na następny węzeł na następny węzeł
        newNode->prev = temp; //ustawiamy wskaźnik na poprzedni węzeł na węzeł
        temp->next->prev = newNode; //ustawiamy wskaźnik na poprzedni węzeł na nowy węzeł
        temp->next = newNode; //ustawiamy wskaźnik na następny węzeł na nowy węzeł
        size++; //zwiększamy licznik elementów
    }
}

template<typename T>
int DoubleLinkedList<T>::find(T element) {
    Node<T>* temp = head; //tworzymy wskaźnik na głowę
    int index = 0; //tworzymy zmienną przechowującą indeks
    while (temp != nullptr) { //dopóki wskaźnik na węzeł nie jest równy nullptr
        if (temp->data == element) { //jeżeli element węzła jest równy szukanemu elementowi
            return index; //zwracamy indeks
        }
        temp = temp->next; //przesuwamy wskaźnik na następny węzeł
        index++; //zwiększamy indeks
    }
    return -1; //jeden jesli element nie zostal znaleziony
}

template class DoubleLinkedList<int>; //deklaracja klasy DoubleLinkedList dla typu int