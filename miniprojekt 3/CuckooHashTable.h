#ifndef MINIPROJEKT_3_CUCKOOHASHTABLE_H
#define MINIPROJEKT_3_CUCKOOHASHTABLE_H

#include <utility>

#include "HashTable.h"

/*
 * Klasa reprezentująca tablicę haszującą z otwartym adresowaniem
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
    CuckooHashTable(int capacity); //konstruktor
    ~CuckooHashTable(); //destruktor
    void insert(int key, int value) override;
    void remove(int key) override;
    int search(int key) override;
};


#endif //MINIPROJEKT_3_CUCKOOHASHTABLE_H
