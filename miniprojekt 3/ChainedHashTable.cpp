#include "ChainedHashTable.h"
#include <iostream>

// Konstruktor inicjalizujący tablicę mieszającą o określonej pojemności
ChainedHashTable::ChainedHashTable(int capacity) : capacity(capacity) {
    table.resize(capacity); // Zmiana rozmiaru wektora na pojemność tablicy, inicjalizacja pustymi listami
}

// Destruktor
ChainedHashTable::~ChainedHashTable() {
    // Nic do zwolnienia, ponieważ std::vector i std::list zarządzają swoją pamięcią automatycznie
}

// Funkcja mieszająca, która oblicza indeks na podstawie klucza
int ChainedHashTable::hash(int key) {
    return key % capacity; // Prosta funkcja mieszająca używająca operacji modulo
}

// Funkcja wstawiająca klucz i wartość do tablicy
void ChainedHashTable::insert(int key, int value) {
    int index = hash(key); // Obliczenie indeksu kubełka
    for (auto& pair : table[index]) { // Iteracja przez listę w kubełku
        if (pair.first == key) { // Jeśli klucz już istnieje, aktualizujemy wartość
            pair.second = value; // Aktualizacja wartości
            return; // Zakończenie funkcji
        }
    }
    table[index].emplace_back(key, value); // Jeśli klucz nie istnieje, dodajemy nową parę klucz-wartość do listy
}

// Funkcja usuwająca klucz z tablicy
void ChainedHashTable::remove(int key) {
    int index = hash(key); // Obliczenie indeksu kubełka
    auto& chain = table[index]; // Referencja do listy w kubełku
    for (auto it = chain.begin(); it != chain.end(); ++it) { // Iteracja przez listę w kubełku
        if (it->first == key) { // Jeśli znajdziemy klucz
            chain.erase(it); // Usuwamy parę klucz-wartość
            return; // Zakończenie funkcji
        }
    }
}

// Funkcja wyszukująca wartość na podstawie klucza
int ChainedHashTable::search(int key) {
    int index = hash(key); // Obliczenie indeksu kubełka
    for (const auto& pair : table[index]) { // Iteracja przez listę w kubełku
        if (pair.first == key) { // Jeśli znajdziemy klucz
            return pair.second; // Zwracamy wartość
        }
    }
    return -1; // Klucz nie został znaleziony
}

// Funkcja wyświetlająca zawartość tablicy mieszającej
void ChainedHashTable::print() const {
    for (int i = 0; i < capacity; ++i) { // Iteracja przez wszystkie kubełki
        std::cout << "Index " << i << ":"; // Wyświetlenie indeksu kubełka
        for (const auto& pair : table[i]) { // Iteracja przez listę w kubełku
            std::cout << " (Key = " << pair.first << ", Value = " << pair.second << ")"; // Wyświetlenie kluczy i wartości
        }
        std::cout << std::endl; // Przejście do nowej linii po wyświetleniu zawartości kubełka
    }
}

// Funkcja zwracająca pojemność tablicy
int ChainedHashTable::getCapacity() const {
    return capacity;
}

// Funkcja czyszcząca tablicę
void ChainedHashTable::clear() {
    for (int i = 0; i < capacity; ++i) { // Iteracja przez wszystkie kubełki
        table[i].clear(); // Wyczyszczenie listy w kubełku
    }
    table.clear(); // Wyczyszczenie całej tablicy
    table.resize(capacity); // Ponowne zainicjalizowanie pustymi listami
}
