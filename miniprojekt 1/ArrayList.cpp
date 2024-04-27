#include "ArrayList.h"

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] array;
}

template<typename T>
void ArrayList<T>::addEnd(T element) {
    if (size == capacity) { //jeżeli liczba elementów jest równa pojemności tablicy
        if(capacity == 0) {
            capacity = 1; //jeżeli pojemność tablicy jest równa 0 to ustawiamy ją na 1 (pierwszy element w tablicy)
        } else {
            capacity *= 2; //podwajamy pojemność tablicy
        }
        T *nowaTablica = new T[capacity]; //tworzymy nową tablicę 2 razy większą od poprzedniej
        for (int i = 0; i < size; i++) {  //przepisujemy elementy z tablicy przedmioty do nowej tablicy
            nowaTablica[i] = array[i];
        }
        nowaTablica[size] = element; //dodajemy nowy element na końcu tablicy
        delete[] array; //zwalniamy pamięć zajmowaną przez starą tablicę
        array = nowaTablica; //przypisujemy nową tablicę do wskaźnika przedmioty
    } else {
        array[size] = element; //dodajemy nowy element na końcu tablicy
    }
    size++; //zwiększamy licznik elementów
}

template<typename T>
void ArrayList<T>::addAt(T element, int index) {
    //zapezpieczenie przed wyjściem poza zakres tablicy
    if (index < 0 || index > size) { //jeżeli indeks jest mniejszy od 0 lub większy od liczby elementów w tablicy
        throw std::out_of_range("Niepoprawny indeks");
    }
    if (size == capacity) { //jeżeli liczba elementów jest równa pojemności tablicy
        if(capacity == 0)
            capacity = 1; //jeżeli pojemność tablicy jest równa 0 to ustawiamy ją na 1 (pierwszy element w tablicy)
        capacity *= 2; //podwajamy pojemność tablicy
        T *nowaTablica = new T[capacity]; //tworzymy nową tablicę 2 razy większą od poprzedniej
        for (int i = 0; i < index; i++) { //przepisujemy elementy z tablicy przedmioty do nowej tablicy
            nowaTablica[i] = array[i];
        }
        nowaTablica[index] = element; //dodajemy nowy element na wskazanym indeksie
        for (int i = index; i < size; i++) { //przepisujemy elementy z tablicy przedmioty do nowej tablicy
            nowaTablica[i + 1] = array[i];
        }
        delete[] array; //zwalniamy pamięć zajmowaną przez starą tablicę
        array = nowaTablica; //przypisujemy nową tablicę do wskaźnika przedmioty
    } else {
        for (int i = size; i > index; i--) { //przesuwamy elementy w tablicy o 1 w prawo
            array[i] = array[i - 1];
        }
        array[index] = element; //dodajemy nowy element na wskazanym indeksie
    }
    size++; //zwiększamy licznik elementów
}

template<typename T>
void ArrayList<T>::addFront(T element) {
    if (size == capacity) { //jeżeli liczba elementów jest równa pojemności tablicy
        if(capacity == 0)
            capacity = 1; //jeżeli pojemność tablicy jest równa 0 to ustawiamy ją na 1 (pierwszy element w tablicy)
        capacity *= 2; //podwajamy pojemność tablicy
        T *nowaTablica = new T[capacity]; //tworzymy nową tablicę 2 razy większą od poprzedniej
        nowaTablica[0] = element; //dodajemy nowy element na początku tablicy
        for (int i = 0; i < size; i++) { //przepisujemy elementy z tablicy przedmioty do nowej tablicy
            nowaTablica[i + 1] = array[i];
        }
        delete[] array; //zwalniamy pamięć zajmowaną przez starą tablicę
        array = nowaTablica; //przypisujemy nową tablicę do wskaźnika przedmioty
    } else {
        for (int i = size; i > 0; i--) { //przesuwamy elementy w tablicy o 1 w prawo
            array[i] = array[i - 1];
        }
        array[0] = element; //dodajemy nowy element na początku tablicy
    }
    size++; //zwiększamy licznik elementów
}

template<typename T>
void ArrayList<T>::removeEnd() {
    if (size == 0) { //jeżeli tablica jest pusta
        throw std::out_of_range("Tablica jest pusta");
    }
    size--; //zmniejszamy licznik elementów
}

template<typename T>
void ArrayList<T>::removeAt(int index) {
    //zapezpieczenie przed wyjściem poza zakres tablicy
    if (index < 0 || index >= size) { //jeżeli indeks jest mniejszy od 0 lub większy od liczby elementów w tablicy
        throw std::out_of_range("Niepoprawny indeks");
    }
    for (int i = index; i < size - 1; i++) { //przesuwamy elementy w tablicy o 1 w lewo
        array[i] = array[i + 1];
    }
    size--; //zmniejszamy licznik elementów
}

template<typename T>
void ArrayList<T>::removeFront() {
    if (size == 0) { //jeżeli tablica jest pusta
        throw std::out_of_range("Tablica jest pusta");
    }
    for (int i = 0; i < size - 1; i++) { //przesuwamy elementy w tablicy o 1 w lewo
        array[i] = array[i + 1];
    }
    size--; //zmniejszamy licznik elementów
}

template<typename T>
void ArrayList<T>::print() {
    for (int i = 0; i < size; i++) { //wyświetlamy elementy tablicy
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void ArrayList<T>::clear() {
    delete[] array; //zwalniamy pamięć zajmowaną przez tablicę
    array = nullptr; //ustawiamy wskaźnik na tablicę na nullptr
    size = 0; //zerujemy licznik elementów
    capacity = 0; //zerujemy pojemność tablicy
}

template<typename T>
int ArrayList<T>::find(T element) {
    for (int i = 0; i < size; i++) { //szukamy elementu w tablicy
        if (array[i] == element) {
            return i; //jeżeli element znajduje się w tablicy to zwracamy jego indeks
        }
    }
    return -1; //jeżeli element nie znajduje się w tablicy to zwracamy -1
}

template class ArrayList<int>; //deklaracja klasy ArrayList dla typu int