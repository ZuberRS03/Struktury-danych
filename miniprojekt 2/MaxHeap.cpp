#include "MaxHeap.h"

void MaxHeap::insert(int e, int p) {
    heap.push_back({e, p}); // dodajemy element na koniec kopca
    heapifyUp(heap.size() - 1); // naprawiamy kopiec w górę
}

std::pair<int, int> MaxHeap::extractMax() {
    if (heap.empty()) throw std::runtime_error("Heap is empty"); // jeżeli kopiec jest pusty, wyrzucamy wyjątek
    std::swap(heap[0], heap.back()); // zamieniamy pierwszy element z ostatnim
    auto maxElement = heap.back(); // zapisujemy element o najwyższym priorytecie
    heap.pop_back(); // usuwamy ostatni element
    heapifyDown(0); // naprawiamy kopiec w dół
    return maxElement; // zwracamy element o najwyższym priorytecie
}

std::pair<int, int> MaxHeap::findMax() const {
    if (heap.empty()) throw std::runtime_error("Heap is empty"); // jeżeli kopiec jest pusty, wyrzucamy wyjątek
    return heap[0]; // zwracamy element o najwyższym priorytecie
}

void MaxHeap::modifyKey(int e, int newP) {
    int index = findIndex(e); // znajdujemy indeks elementu
    if (index == -1) throw std::runtime_error("Element not found"); // jeżeli element nie został znaleziony, wyrzucamy wyjątek
    heap[index].second = newP; // zmieniamy priorytet elementu
    heapifyUp(index); // naprawiamy kopiec w górę
    heapifyDown(index); // naprawiamy kopiec w dół
}

size_t MaxHeap::returnSize() const {
    return heap.size(); // zwracamy rozmiar kopca
}

void MaxHeap::heapifyUp(int index) {
    while (index > 0) { // dopóki indeks jest większy od 0
        int parentIndex = (index - 1) / 2; // obliczamy indeks rodzica
        if (heap[index].second > heap[parentIndex].second) { // jeżeli element jest większy od rodzica
            std::swap(heap[index], heap[parentIndex]); // zamieniamy element z rodzicem
            index = parentIndex; // ustawiamy indeks na indeks rodzica
        } else { // jeżeli element jest mniejszy od rodzica
            break; // przerywamy pętlę
        }
    }
}

void MaxHeap::heapifyDown(int index) {
    int size = heap.size(); // zapisujemy rozmiar kopca
    while (true) { // dopóki prawda
        int left = 2 * index + 1; // obliczamy indeks lewego dziecka
        int right = 2 * index + 2; // obliczamy indeks prawego dziecka
        int largest = index; // ustawiamy największy element na indeks

        if (left < size && heap[left].second > heap[largest].second) { // jeżeli lewe dziecko istnieje i jest większe od największego elementu
            largest = left; // ustawiamy największy element na lewe dziecko
        }
        if (right < size && heap[right].second > heap[largest].second) { // jeżeli prawe dziecko istnieje i jest większe od największego elementu
            largest = right; // ustawiamy największy element na prawe dziecko
        }

        if (largest != index) { // jeżeli największy element nie jest równy indeksowi
            std::swap(heap[index], heap[largest]); // zamieniamy element z największym elementem
            index = largest; // ustawiamy indeks na największy element
        } else { // jeżeli największy element jest równy indeksowi
            break; // przerywamy pętlę
        }
    }
}

int MaxHeap::findIndex(int e) {
    for (int i = 0; i < heap.size(); i++) { // szukamy elementu w kopcu
        if (heap[i].first == e) return i; // jeżeli element znajduje się w kopcu, zwracamy jego indeks
    }
    return -1; // jeżeli element nie znajduje się w kopcu, zwracamy -1
}

void MaxHeap::print() const {
    for (const auto& elem : heap) { // dla każdego elementu w kopcu
        std::cout << elem.first << " " << elem.second << std::endl; // wyświetlamy element
    }
}

void MaxHeap::clearHeap() {
    heap.clear(); // czyścimy kopiec
}

bool MaxHeap::isHeapValid() const {
    for (int i = 0; i < heap.size(); i++) { // dla każdego elementu w kopcu
        int left = 2 * i + 1; // obliczamy indeks lewego dziecka
        int right = 2 * i + 2; // obliczamy indeks prawego dziecka
        if ((left < heap.size() && heap[i].second < heap[left].second) ||
            (right < heap.size() && heap[i].second < heap[right].second)) { // jeżeli element jest mniejszy od któregoś z dzieci
            return false; // zwracamy fałsz
        }
    }
    return true; // zwracamy prawdę
}