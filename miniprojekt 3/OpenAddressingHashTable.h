#ifndef MINIPROJEKT_3_OPENADDRESSINGHASHTABLE_H
#define MINIPROJEKT_3_OPENADDRESSINGHASHTABLE_H

#include "HashTable.h"
/*
 * Klasa reprezentująca tablicę haszującą z otwartym adresowaniem
 * Dziedziczy po klasie HashTable
 * Funkcje prywatne hash, probe
 */
class OpenAddressingHashTable : public HashTable{
private:
    int* table; //tablica kluczy
    int capacity; //pojemność tablicy
    int size; //rozmiar tablicy
    int hash(int key); //funkcja haszująca
    int probe(int key); //funkcja przeszukująca

public:
    OpenAddressingHashTable(int capacity); //konstruktor
    ~OpenAddressingHashTable(); //destruktor
    void insert(int key, int value) override;
    void remove(int key) override;
    int search(int key) override;
};


#endif //MINIPROJEKT_3_OPENADDRESSINGHASHTABLE_H
