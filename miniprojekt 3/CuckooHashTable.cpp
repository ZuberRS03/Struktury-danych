#include "CuckooHashTable.h"
#include <iostream>
#include <stdexcept>

// Konstruktor inicjalizujący tablicę mieszającą o określonej pojemności
CuckooHashTable::CuckooHashTable(int capacity) : capacity(capacity), size(0) {
    table1 = new std::pair<int, int>[capacity]; // Alokacja pamięci na pierwszą tablicę
    table2 = new std::pair<int, int>[capacity]; // Alokacja pamięci na drugą tablicę
    for (int i = 0; i < capacity; ++i) {
        table1[i] = {-1, -1}; // Inicjalizacja pierwszej tablicy wartością -1, co oznacza, że pozycja jest pusta
        table2[i] = {-1, -1}; // Inicjalizacja drugiej tablicy wartością -1, co oznacza, że pozycja jest pusta
    }
}

// Destruktor zwalniający zarezerwowaną pamięć
CuckooHashTable::~CuckooHashTable() {
    delete[] table1;
    delete[] table2;
}

// Pierwsza funkcja mieszająca, która oblicza indeks na podstawie klucza
int CuckooHashTable::hash1(int key) {
    return key % capacity;
}

// Druga funkcja mieszająca, która oblicza indeks na podstawie klucza
int CuckooHashTable::hash2(int key) {
    return (key / capacity) % capacity;
}

// Funkcja do ponownego haszowania tablic
void CuckooHashTable::rehash() {
    int oldCapacity = capacity; // Zapisanie starej pojemności tablic
    capacity *= 2; // Podwojenie pojemności tablic

    std::pair<int, int>* oldTable1 = table1; // Zapisanie starej tablicy 1
    std::pair<int, int>* oldTable2 = table2; // Zapisanie starej tablicy 2

    table1 = new std::pair<int, int>[capacity]; // Alokacja pamięci na nową tablicę 1
    table2 = new std::pair<int, int>[capacity]; // Alokacja pamięci na nową tablicę 2
    for (int i = 0; i < capacity; ++i) { // Inicjalizacja nowych tablic wartościami -1
        table1[i] = {-1, -1}; // Inicjalizacja pierwszej tablicy wartością -1, co oznacza, że pozycja jest pusta
        table2[i] = {-1, -1}; // Inicjalizacja drugiej tablicy wartością -1, co oznacza, że pozycja jest pusta
    }

    size = 0; // Resetowanie rozmiaru

    // Przenoszenie elementów z starej tablicy do nowej
    for (int i = 0; i < oldCapacity; ++i) {
        if (oldTable1[i].first != -1) { // Sprawdzenie, czy element istnieje w starej tablicy 1
            insert(oldTable1[i].first, oldTable1[i].second); // Wstawienie elementu do nowej tablicy
        }
        if (oldTable2[i].first != -1) { // Sprawdzenie, czy element istnieje w starej tablicy 2
            insert(oldTable2[i].first, oldTable2[i].second); // Wstawienie elementu do nowej tablicy
        }
    }

    delete[] oldTable1; // Zwolnienie pamięci po starej tablicy 1
    delete[] oldTable2; // Zwolnienie pamięci po starej tablicy 2
}

// Funkcja wstawiająca klucz i wartość do tablicy z użyciem haszowania kukułczego
void CuckooHashTable::insert(int key, int value) {
    int index1 = hash1(key); // Obliczenie indeksu w pierwszej tablicy
    if (table1[index1].first == -1) { // Sprawdzenie, czy miejsce jest puste
        table1[index1] = {key, value}; // Wstawienie klucza i wartości do pierwszej tablicy, jeśli miejsce jest puste
        ++size; // Zwiększenie rozmiaru tablicy
        return; // Zakończenie funkcji
    }

    std::swap(key, table1[index1].first); // Wymiana klucza z już istniejącym kluczem w pierwszej tablicy
    std::swap(value, table1[index1].second); // Wymiana wartości z już istniejącą wartością w pierwszej tablicy

    int index2 = hash2(key); // Obliczenie indeksu w drugiej tablicy
    if (table2[index2].first == -1) { // Sprawdzenie, czy miejsce jest puste
        table2[index2] = {key, value}; // Wstawienie klucza i wartości do drugiej tablicy, jeśli miejsce jest puste
        ++size; // Zwiększenie rozmiaru tablicy
        return; // Zakończenie funkcji
    }

    std::swap(key, table2[index2].first); // Wymiana klucza z już istniejącym kluczem w drugiej tablicy
    std::swap(value, table2[index2].second); // Wymiana wartości z już istniejącą wartością w drugiej tablicy

    // Jeśli osiągniemy ten punkt, oznacza to, że musimy przeprowadzić ponowne haszowanie
    rehash();
    insert(key, value); // Ponowna próba wstawienia po przehaszowaniu
}

// Funkcja usuwająca klucz z tablicy
void CuckooHashTable::remove(int key) {
    int index1 = hash1(key); // Obliczenie indeksu w pierwszej tablicy
    if (table1[index1].first == key) { // Sprawdzenie, czy klucz znajduje się w pierwszej tablicy
        table1[index1] = {-1, -1}; // Oznaczenie pozycji jako pustej w pierwszej tablicy
        --size; // Zmniejszenie rozmiaru tablicy
        return; // Zakończenie funkcji
    }

    int index2 = hash2(key); // Obliczenie indeksu w drugiej tablicy
    if (table2[index2].first == key) { // Sprawdzenie, czy klucz znajduje się w drugiej tablicy
        table2[index2] = {-1, -1}; // Oznaczenie pozycji jako pustej w drugiej tablicy
        --size; // Zmniejszenie rozmiaru tablicy
        return; // Zakończenie funkcji
    }
}

// Funkcja wyszukująca wartość na podstawie klucza
int CuckooHashTable::search(int key) {
    int index1 = hash1(key); // Obliczenie indeksu w pierwszej tablicy
    if (table1[index1].first == key) { // Sprawdzenie, czy klucz znajduje się w pierwszej tablicy
        return table1[index1].second; // Zwrócenie wartości z pierwszej tablicy, jeśli klucz został znaleziony
    }

    int index2 = hash2(key); // Obliczenie indeksu w drugiej tablicy
    if (table2[index2].first == key) { // Sprawdzenie, czy klucz znajduje się w drugiej tablicy
        return table2[index2].second; // Zwrócenie wartości z drugiej tablicy, jeśli klucz został znaleziony
    }

    return -1; // Klucz nie został znaleziony
}

// Funkcja wyświetlająca zawartość tablicy mieszającej
void CuckooHashTable::print() const {
    std::cout << "Table 1:" << std::endl;
    for (int i = 0; i < capacity; ++i) {
        if (table1[i].first != -1) {
            std::cout << "Index " << i << ": Key = " << table1[i].first << ", Value = " << table1[i].second << std::endl;
        } else {
            std::cout << "Index " << i << ": Empty" << std::endl;
        }
    }

    std::cout << "Table 2:" << std::endl;
    for (int i = 0; i < capacity; ++i) {
        if (table2[i].first != -1) {
            std::cout << "Index " << i << ": Key = " << table2[i].first << ", Value = " << table2[i].second << std::endl;
        } else {
            std::cout << "Index " << i << ": Empty" << std::endl;
        }
    }
}

// Funkcja zwracająca pojemność tablicy
int CuckooHashTable::getCapacity() const {
    return capacity;
}

// Funkcja czyszcząca tablicę
void CuckooHashTable::clear() {
    for (int i = 0; i < capacity; ++i) {
        table1[i] = {-1, -1}; // Inicjalizacja pierwszej tablicy wartością -1, co oznacza, że pozycja jest pusta
        table2[i] = {-1, -1}; // Inicjalizacja drugiej tablicy wartością -1, co oznacza, że pozycja jest pusta
    }
    size = 0; // Resetowanie rozmiaru
}