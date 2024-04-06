#ifndef MINIPROJEKT_1_ARRAYLIST_H
#define MINIPROJEKT_1_ARRAYLIST_H

#include <iostream>

template <typename T>
class ArrayList {
private:
    int size; //licznik elementów w tablicy
    int capacity; //pojemność tablicy
    T *array; //tablica przechowująca elementy
public:
    ArrayList() : size{ 0 }, capacity{ 0 }, array{ nullptr } {} //konstruktor
    ~ArrayList(); //destruktor

    void addEnd(T element); //metoda dodająca element do tablicy na końcu
    void addAt(T element, int index); //metoda dodająca element na podanym indeksie
    void addFront(T element); //metoda dodająca element na początku tablicy
    void usunElement(int index); //metoda usuwająca element z tablicy
    void print(); //metoda wypisująca elementy tablicy
    void clear(); //metoda czyszcząca tablicę
    int find(T element); //metoda wyszukująca element w tablicy
};

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] array;
}

template<typename T>
void ArrayList<T>::addEnd(T element) {
    if (size == capacity) { //jeżeli liczba elementów jest równa pojemności tablicy
        if(capacity == 0)
            capacity = 1; //jeżeli pojemność tablicy jest równa 0 to ustawiamy ją na 1 (pierwszy element w tablicy)
        capacity *= 2; //podwajamy pojemność tablicy
        T *nowaTablica = new T[capacity]; //tworzymy nową tablicę o 1 większą
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
    if (index < 0 || index > size) {
        throw std::out_of_range("Niepoprawny indeks");
    }
    if (size == capacity) {
        if(capacity == 0)
            capacity = 1;
        capacity *= 2;
        T *nowaTablica = new T[capacity];
        for (int i = 0; i < index; i++) {
            nowaTablica[i] = array[i];
        }
        nowaTablica[index] = element;
        for (int i = index; i < size; i++) {
            nowaTablica[i + 1] = array[i];
        }
        delete[] array;
        array = nowaTablica;
    } else {
        for (int i = size; i > index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = element;
    }
    size++;
}

template<typename T>
void ArrayList<T>::addFront(T element) {
    if (size == capacity) {
        if(capacity == 0)
            capacity = 1;
        capacity *= 2;
        T *nowaTablica = new T[capacity];
        nowaTablica[0] = element;
        for (int i = 0; i < size; i++) {
            nowaTablica[i + 1] = array[i];
        }
        delete[] array;
        array = nowaTablica;
    } else {
        for (int i = size; i > 0; i--) {
            array[i] = array[i - 1];
        }
        array[0] = element;
    }
    size++;
}

template<typename T>
void ArrayList<T>::usunElement(int index) {
    //zapezpieczenie przed wyjściem poza zakres tablicy
    if (index < 0 || index >= size) {
        throw std::out_of_range("Niepoprawny indeks");
    }
    T *nowaTablica = new T[size - 1];
    for (int i = 0; i < index; i++) {
        nowaTablica[i] = array[i];
    }
    for (int i = index + 1; i < size; i++) {
        nowaTablica[i - 1] = array[i];
    }
    delete[] array;
    array = nowaTablica;
    size--;
}

template<typename T>
void ArrayList<T>::print() {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void ArrayList<T>::clear() {
    delete[] array;
    array = nullptr;
    size = 0;
}

template<typename T>
int ArrayList<T>::find(T element) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return i;
        }
    }
    return -1;
}

#endif //MINIPROJEKT_1_ARRAYLIST_H
