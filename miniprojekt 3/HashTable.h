#ifndef MINIPROJEKT_3_HASHTABLE_H
#define MINIPROJEKT_3_HASHTABLE_H

/*
 * Interfejs klasy reprezentującej tablicę haszującą
 * Deklaracja metod wirutalnych insert, remove, search, print
 * Destruktor wirtualny
 */
class HashTable {
public:
    virtual void insert(int key, int value) = 0; //funkcja wirtualna dodająca element do tablicy
    virtual void remove(int key) = 0; //funkcja wirtualna usuwająca element z tablicy
    virtual int search(int key) = 0; //funkcja wirtualna wyszukująca element w tablicy
    virtual void print() const = 0;
    virtual int getCapacity() const = 0;
    virtual void clear() = 0;
    virtual ~HashTable() = default; //destruktor wirtualny
};

#endif //MINIPROJEKT_3_HASHTABLE_H
