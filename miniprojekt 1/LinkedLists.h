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

    /*
     * @brief Metoda dodająca element na początku listy
     * @param data - wartość elementu, który ma zostać dodany
     * @return void
     */
    void addFront(T data);

    /*
     * @brief Metoda dodająca element na końcu listy
     * @param data - wartość elementu, który ma zostać dodany
     * @return void
     */
    void addEnd(T data);

    /*
     * @brief Metoda dodająca element na podanym indeksie
     * @param data - wartość elementu, który ma zostać dodany
     * @param index - indeks, na którym ma zostać dodany element
     * @return void
     */
    void addAt(T data, int index);

    /*
     * @brief Metoda wyszukująca element w liście
     * @param element - element, który chcemy znaleźć
     * @return int - indeks elementu w liście
     */
    int find(T element);

    /*
     * @brief Metoda usuwająca element z początku listy
     * @return void
     */
    void removeFront();

    /*
     * @brief Metoda usuwająca element z końca listy
     * @return void
     */
    void removeEnd();

    /*
     * @brief Metoda usuwająca element na podanym indeksie
     * @param index - indeks elementu, który chcemy usunąć
     * @return void
     */
    void removeAt(int index);

    /*
     * @brief Metoda wyświetlająca wszystkie elementy listy
     * @return void
     */
    void print();

    /*
     * @brief Metoda czyszcząca listę
     * @return void
     */
    void clear();
};



#endif // LINKEDLIST_H