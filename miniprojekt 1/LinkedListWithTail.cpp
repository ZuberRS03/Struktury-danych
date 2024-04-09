#include "LinkedListWithTail.h"

template<typename T>
LinkedListWithTail<T>::~LinkedListWithTail() {
    clear();
}

template<typename T>
void LinkedListWithTail<T>::addFront(T data) {
    Node<T>* newNode = new Node<T>(data);
    if(head == nullptr) { // Jeśli lista jest pusta, nowy węzeł jest również ogonem
        head = newNode; // Ustawienie wskaźnika na głowę na nowy węzeł
        tail = newNode; // Ustawienie wskaźnika na ogon na nowy węzeł
    } else { // Jeśli lista nie jest pusta
        newNode->next = head; // Ustawienie wskaźnika na następny węzeł nowego węzła na obecny wskaźnik na głowę
        head = newNode; // Ustawienie wskaźnika na głowę na nowy węzeł
    }
    size++; // Zwiększenie licznika elementów
}

template<typename T>
void LinkedListWithTail<T>::addEnd(T data) {
    Node<T>* newNode = new Node<T>(data); // Utworzenie nowego węzła
    if (head == nullptr) { // Jeśli lista jest pusta
        head = tail = newNode; // Ustawienie wskaźnika na głowę i ogon na nowy węzeł
    } else { // Jeśli lista nie jest pusta
        tail->next = newNode; // Ustawienie wskaźnika na następny węzeł obecnego ogona na nowy węzeł
        tail = tail->next; // Przesunięcie wskaźnika na ogon na nowy węzeł
    }
    size++; // Zwiększenie licznika elementów
}

template<typename T>
void LinkedListWithTail<T>::addAt(T data, int index) {
    if (index < 0 || index > size) { // Jeśli indeks jest mniejszy od 0 lub większy od liczby elementów w liście
        throw std::out_of_range("Niepoprawny indeks");
    }
    if (index == 0) { // Jeśli indeks jest równy 0
        addFront(data); // Dodanie nowego elementu na początku listy
    } else if (index == size) { // Jeśli indeks jest równy liczbie elementów w liście
        addEnd(data); // Dodanie nowego elementu na końcu listy
    } else { // Jeśli indeks jest większy od 0 i mniejszy od liczby elementów w liście
        Node<T>* newNode = new Node<T>(data); // Utworzenie nowego węzła
        Node<T>* temp = head; // Utworzenie wskaźnika na głowę
        for (int i = 0; i < index - 1; i++) { // Przesunięcie wskaźnika na węzeł o indeksie o 1
            temp = temp->next; // Przesunięcie wskaźnika na następny węzeł
        }
        newNode->next = temp->next; // Ustawienie wskaźnika na następny węzeł nowego węzła na następny węzeł
        temp->next = newNode; // Ustawienie wskaźnika na następny węzeł na nowy węzeł
        size++; // Zwiększenie licznika elementów
    }
}

template<typename T>
int LinkedListWithTail<T>::find(T element) {
    Node<T>* temp = head; // Utworzenie wskaźnika na głowę
    int index = 0; // Utworzenie zmiennej przechowującej indeks
    while (temp != nullptr) { // Dopóki wskaźnik na węzeł nie jest równy nullptr
        if (temp->data == element) { // Jeśli element węzła jest równy szukanemu elementowi
            return index; // Zwrócenie indeksu
        }
        temp = temp->next; // Przesunięcie wskaźnika na następny węzeł
        index++; // Zwiększenie indeksu
    }
    return -1; // Jeśli nie znaleziono elementu zwrócenie -1
}

template<typename T>
void LinkedListWithTail<T>::removeFront() {
    if (head == nullptr) return; // Jeśli lista jest pusta, zakończenie funkcji
    Node<T>* temp = head; // Utworzenie wskaźnika na głowę
    head = head->next;  // Przesunięcie wskaźnika na głowę na następny węzeł
    if (head == nullptr) { // Jeśli wskaźnik na głowę jest równy nullptr
        tail = nullptr; // Ustawienie wskaźnika na ogon na nullptr
    }
    delete temp; // Zwolnienie pamięci zajmowanej przez wskaźnik na węzeł
    size--; // Zmniejszenie licznika elementów
}

template<typename T>
void LinkedListWithTail<T>::removeEnd() {
    if (head == nullptr) return; // Jeśli lista jest pusta, zakończenie funkcji
    if (head == tail) { // Jeśli wskaźnik na głowę jest równy wskaźnikowi na ogon
        delete head; // Zwolnienie pamięci zajmowanej przez wskaźnik na głowę
        head = tail = nullptr; // Ustawienie wskaźników na głowę i ogon na nullptr
    } else { // Jeśli wskaźnik na głowę nie jest równy wskaźnikowi na ogon
        Node<T>* temp = head; // Utworzenie wskaźnika na głowę
        while (temp->next != tail) { // Dopóki wskaźnik na następny węzeł nie jest równy wskaźnikowi na ogon
            temp = temp->next; // Przesunięcie wskaźnika na następny węzeł
        }
        delete tail; // Zwolnienie pamięci zajmowanej przez wskaźnik na ogon
        tail = temp; // Przesunięcie wskaźnika na ogon na poprzedni węzeł
        tail->next = nullptr; // Ustawienie wskaźnika na następny węzeł na nullptr
    }
}

template<typename T>
void LinkedListWithTail<T>::removeAt(int index) {
    if (index < 0 || index >= size) { // Jeśli indeks jest mniejszy od 0 lub większy od liczby elementów w liście
        throw std::out_of_range("Niepoprawny indeks");
    }
    if (index == 0) { // Jeśli indeks jest równy 0
        removeFront(); // Usunięcie pierwszego elementu
    } else if (index == size - 1) { // Jeśli indeks jest równy liczbie elementów w liście - 1
        removeEnd(); // Usunięcie ostatniego elementu
    } else { // Jeśli indeks jest większy od 0 i mniejszy od liczby elementów w liście - 1
        Node<T>* temp = head; // Utworzenie wskaźnika na głowę
        for (int i = 0; i < index - 1; i++) { // Przesunięcie wskaźnika na węzeł o indeksie o 1
            temp = temp->next; // Przesunięcie wskaźnika na następny węzeł
        }
        Node<T>* toDelete = temp->next; // Utworzenie wskaźnika na węzeł do usunięcia
        temp->next = temp->next->next; // Ustawienie wskaźnika na następny węzeł na następny węzeł
        delete toDelete; // Zwolnienie pamięci zajmowanej przez wskaźnik na węzeł
        size--; // Zmniejszenie licznika elementów
    }
}

template<typename T>
void LinkedListWithTail<T>::print() {
    Node<T>* temp = head; // Utworzenie wskaźnika na głowę
    while (temp != nullptr) { // Dopóki wskaźnik na węzeł nie jest równy nullptr
        std::cout << temp->data << " "; // Wyświetlenie elementu węzła
        temp = temp->next; // Przesunięcie wskaźnika na następny węzeł
    }
    std::cout << std::endl;
}

template<typename T>
void LinkedListWithTail<T>::clear() {
    while (head != nullptr) { // Dopóki wskaźnik na głowę nie jest równy nullptr
        Node<T>* temp = head; // Utworzenie wskaźnika na głowę
        head = head->next; // Przesunięcie wskaźnika na głowę na następny węzeł
        delete temp; // Zwolnienie pamięci zajmowanej przez wskaźnik na węzeł
    }
    tail = nullptr; // Ustawienie wskaźnika na ogon na nullptr
    size = 0; // Zerowanie licznika elementów
}

template class LinkedListWithTail<int>; // Deklaracja wymagana przez kompilator dla szablonów

