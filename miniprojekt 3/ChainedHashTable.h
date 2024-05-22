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
    int capacity; //pojemność tablicy
    int hash(int key); //funkcja haszująca

public:
    ChainedHashTable(int capacity); //konstruktor
    ~ChainedHashTable(); //destruktor
    void insert(int key, int value) override;
    void remove(int key) override;
    int search(int key) override;
};


#endif //MINIPROJEKT_3_CHAINEDHASHTABLE_H
