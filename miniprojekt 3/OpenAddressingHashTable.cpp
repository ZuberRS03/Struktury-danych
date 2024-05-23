#include "OpenAddressingHashTable.h"

#include <iostream>

// Konstruktor inicjalizujący tablicę mieszającą o określonej pojemności
OpenAddressingHashTable::OpenAddressingHashTable(int capacity) : capacity(capacity), size(0) {
    table = new int[capacity];   // Alokacja pamięci na tablicę kluczy
    values = new int[capacity];  // Alokacja pamięci na tablicę wartości

    // Inicjalizacja tablicy kluczy wartością -1, co oznacza, że pozycja jest pusta
    for (int i = 0; i < capacity; ++i) {
        table[i] = -1; // Oznaczenie pozycji jako pustej
    }
}

// Destruktor zwalniający zarezerwowaną pamięć
OpenAddressingHashTable::~OpenAddressingHashTable() {
    delete[] table;
    delete[] values;
}

// Funkcja mieszająca, która oblicza indeks na podstawie klucza
int OpenAddressingHashTable::hash(int key) {
    return key % capacity; // Zwrócenie indeksu
}

// Funkcja sondowania, która znajduje odpowiedni indeks dla klucza
int OpenAddressingHashTable::probe(int key) {
    int index = hash(key);  // Obliczenie podstawowego indeksu
    int i = 0; //Zmienna skoku w przypadku kolizji
    int deleted_position = -1; // Zmienna przechowująca indeks pierwszej napotkanej pozycji oznaczonej jako "usunięta"

    // Szukanie pustej pozycji lub pozycji z danym kluczem
    while (table[(index + i) % capacity] != -1 && table[(index + i) % capacity] != key) {
        if (table[(index + i) % capacity] == DELETED_KEY && deleted_position == -1) {
            deleted_position = (index + i) % capacity; // Zapisanie indeksu pozycji oznaczonej jako "usunięta"
        }
        ++i; // Zwiększenie zmiennej skoku o 1
    }

    // Jeżeli znaleziono pozycję oznaczoną jako "usunięta" i nie znaleziono pozycji z danym kluczem, zwróć indeks pozycji oznaczonej jako "usunięta"
    if (table[(index + i) % capacity] == -1 && deleted_position != -1) {
        return deleted_position;
    }

    return (index + i) % capacity; // Zwrócenie znalezionego indeksu
}

// Funkcja wstawiająca klucz i wartość do tablicy
void OpenAddressingHashTable::insert(int key, int value) {
    int index = probe(key);  // Znalezienie odpowiedniego indeksu
    if (table[index] == DELETED_KEY) { // Jeżeli pozycja jest oznaczona jako usunięta
        --size; // Zmniejszenie rozmiaru tablicy, ponieważ będziemy wstawiać na to miejsce
    }
    table[index] = key;      // Wstawienie klucza
    values[index] = value;   // Wstawienie wartości
    ++size;                  // Zwiększenie rozmiaru tablicy
}

// Funkcja usuwająca klucz z tablicy
void OpenAddressingHashTable::remove(int key) {
    int index = hash(key);   // Obliczenie podstawowego indeksu
    int i = 0; //Zmienna skoku w przypadku kolizji

    // Szukanie klucza w tablicy
    // % capacity zapewnia, że nie wychodzimy poza zakres tablicy
    while (table[(index + i) % capacity] != -1) { // Dopóki nie znajdziemy pustej pozycji
        if (table[(index + i) % capacity] == key) { // Jeżeli klucz został znaleziony
            table[(index + i) % capacity] = DELETED_KEY; // Oznaczenie pozycji jako pustej
            values[(index + i) % capacity] = -1; // Oznaczenie wartości jako pustej
            --size; // Zmniejszenie rozmiaru tablicy
            return; // Zakończenie funkcji
        }
        ++i; // Zwiększenie zmiennej skoku o 1
    }
}

// Funkcja wyszukująca wartość na podstawie klucza
int OpenAddressingHashTable::search(int key) {
    int index = hash(key);  // Obliczenie podstawowego indeksu
    int i = 0; //Zmienna skoku w przypadku kolizji

    // Szukanie klucza w tablicy
    // % capacity zapewnia, że nie wychodzimy poza zakres tablicy
    while (table[(index + i) % capacity] != -1) {  // Dopóki nie znajdziemy pustej pozycji
        if (table[(index + i) % capacity] == key) { // Jeżeli klucz został znaleziony
            return values[(index + i) % capacity]; // Zwrócenie znalezionej wartości
        }
        ++i; // Zwiększenie zmiennej skoku o 1
    }
    return -1; // Klucz nie został znaleziony
}

// Funkcja wyświetlająca zawartość tablicy mieszającej
void OpenAddressingHashTable::print() const {
    for (int i = 0; i < capacity; ++i) { // Przejście przez całą tablicę
        if (table[i] != -1) { // Jeżeli pozycja nie jest pusta
            std::cout << "Index " << i << ": Key = " << table[i] << ", Value = " << values[i] << std::endl;
        } else { // Jeżeli pozycja jest pusta
            std::cout << "Index " << i << ": Empty" << std::endl;
        }
    }
}