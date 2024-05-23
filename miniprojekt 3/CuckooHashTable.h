#ifndef MINIPROJEKT_3_CUCKOOHASHTABLE_H
#define MINIPROJEKT_3_CUCKOOHASHTABLE_H

#include <utility>

#include "HashTable.h"

/*
 * Klasa reprezentująca tablicę mieszającą z haszowaniem kukułczym
 * Dziedziczy po klasie HashTable
 * Funkcje prywatne hash1, hash2, rehash
 */
class CuckooHashTable : public HashTable{
private:
    std::pair<int, int>* table1; //tablica 1 par klucz-wartość
    std::pair<int, int>* table2; //tablica 2 par klucz-wartość
    int capacity; //pojemność tablic
    int size; //rozmiar tablic

    int hash1(int key); //funkcja haszująca 1
    int hash2(int key); //funkcja haszująca 2
    void rehash(); //funkcja rehaszująca tablice

public:
    //konstruktor
    CuckooHashTable(int capacity);

    //destruktor
    ~CuckooHashTable();

    /*
     * Funkcja wstawiająca parę klucz-wartość do tablicy
     * @param key - klucz
     * @param value - wartość
     * @return void
     */
    void insert(int key, int value) override;

    /*
     * Funkcja usuwająca parę klucz-wartość z tablicy
     * @param key - klucz
     * @return void
     */
    void remove(int key) override;

    /*
     * Funkcja wyszukująca wartość dla danego klucza
     * @param key - klucz
     * @return wartość
     */
    int search(int key) override;

    /*
     * Funkcja wypisująca tablicę
     * @return void
     */
    void print() const override;

    /*
     * Funkcja zwracająca pojemność tablicy
     * @return pojemność
     */
    int getCapacity() const override;

    /*
     * Funkcja czyszcząca tablicę
     * @return void
     */
    void clear() override;
};


#endif //MINIPROJEKT_3_CUCKOOHASHTABLE_H
