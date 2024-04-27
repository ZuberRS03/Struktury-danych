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
    //konstruktor
    ArrayList() : size{ 0 }, capacity{ 0 }, array{ nullptr } {}

    //destruktor
    ~ArrayList();

    /*
     * @brief Metoda dodająca element do tablicy na końcu
     * @param element - element, który chcemy dodać
     * @return void
     */
    void addEnd(T element);

    /*
     * @brief Metoda dodająca element do tablicy na podanym indeksie
     * @param element - element, który chcemy dodać
     * @param index - indeks, na którym chcemy dodać element
     * @return void
     */
    void addAt(T element, int index);

    /*
     * @brief Metoda dodająca element do tablicy na początku
     * @param element - element, który chcemy dodać
     * @return void
     */
    void addFront(T element);

    /*
     * @brief Metoda usuwająca ostatni element z tablicy
     * @return void
     */
    void removeEnd();

    /*
     * @brief Metoda usuwająca element z tablicy na podanym indeksie
     * @param index - indeks, z którego chcemy usunąć element
     * @return void
     */
    void removeAt(int index);

    /*
     * @brief Metoda usuwająca pierwszy element z tablicy
     * @return void
     */
    void removeFront();

    /*
     * @brief Metoda wypisująca elementy tablicy
     * @return void
     */
    void print();

    /*
     * @brief Metoda czyszcząca tablicę
     * @return void
     */
    void clear();

    /*
     * @brief Metoda wyszukująca element w tablicy
     * @param element - element, który chcemy wyszukać
     * @return int - indeks elementu w tablicy
     */
    int find(T element);

    /*
     * @brief Metoda zwracająca liczbę elementów w tablicy
     * @return int - liczba elementów w tablicy
     */
    int getSize() { return size; }

    /*
     * @brief Metoda zwracająca pojemność tablicy
     * @return int - pojemność tablicy
     */
    int getCapacity() { return capacity; }
};

#endif //MINIPROJEKT_1_ARRAYLIST_H
