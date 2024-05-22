#ifndef MINIPROJEKT_3_CHAINEDHASHTABLE_H
#define MINIPROJEKT_3_CHAINEDHASHTABLE_H

#include <list>
#include <vector>

#include "HashTable.h"
/*
 * Klasa reprezentująca tablicę haszującą z łańcuchami
 * Dziedziczy po klasie HashTable
 * Funkcje prywatne hash
 * Wykorzystanie list wiązanych do obsługi kolizji
 */
class ChainedHashTable : public HashTable{
private:
    std::vector<std::list<std::pair<int, int>>> table; //wektor list par klucz-wartość
    int capacity; //pojemność tablicy / liczba kubełków

    int hash(int key); //funkcja haszująca

public:
    //konstruktor
    ChainedHashTable(int capacity);

    //destruktor
    ~ChainedHashTable();

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
};


#endif //MINIPROJEKT_3_CHAINEDHASHTABLE_H
