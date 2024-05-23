#ifndef MINIPROJEKT_3_OPENADDRESSINGHASHTABLE_H
#define MINIPROJEKT_3_OPENADDRESSINGHASHTABLE_H

#include "HashTable.h"
/*
 * Klasa reprezentująca tablicę haszującą z otwartym adresowaniem
 * Dziedziczy po klasie HashTable
 * Funkcje prywatne hash, probe
 * Wykorzystanie tablicy kluczy i wartości do obsługi kolizji
 */
class OpenAddressingHashTable : public HashTable{
private:
    int* table; //tablica kluczy
    int* values; //tablica wartości
    int capacity; //pojemność tablicy
    int size; //rozmiar tablicy
    const int DELETED_KEY = -2; // Stała oznaczająca usunięty klucz

    int hash(int key); //funkcja haszująca
    int probe(int key);  //funkcja przeszukująca/sondowania

public:
    //konstruktor
    OpenAddressingHashTable(int capacity);

    //destruktor
    ~OpenAddressingHashTable();

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


#endif //MINIPROJEKT_3_OPENADDRESSINGHASHTABLE_H
