#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class MaxHeap {
private:
    std::vector<std::pair<int, int>> heap; // kopiec przechowujący elementy

    /*
     * @brief Metoda naprawiająca kopiec w górę
     * @param index - indeks elementu, który chcemy "naprawić"
     * @return void
     */
    void heapifyUp(int index);

    /*
     * @brief Metoda naprawiająca kopiec w dół
     * @param index - indeks elementu, który chcemy "naprawić"
     * @return void
     */
    void heapifyDown(int index);

    /*
     * @brief Metoda znajdująca indeks elementu w kopcu
     * @param e - element, którego indeks chcemy znaleźć
     * @return int - indeks elementu
     */
    int findIndex(int e);

public:
    /*
     * @brief Metoda dodająca element do kopca
     * @param e - element, który chcemy dodać
     * @param p - priorytet elementu
     * @return void
     */
    void insert(int e, int p);

    /*
     * @brief Metoda usuwająca element o najwyższym priorytecie z kopca
     * @return std::pair<int, int> - element o najwyższym priorytecie
     */
    std::pair<int, int> extractMax();

    /*
     * @brief Metoda zwracająca element o najwyższym priorytecie z kopca
     * @return std::pair<int, int> - element o najwyższym priorytecie
     */
    std::pair<int, int> findMax() const;

    /*
     * @brief Metoda modyfikująca priorytet elementu w kopcu
     * @param e - element, którego priorytet chcemy zmodyfikować
     * @param newP - nowy priorytet elementu
     * @return void
     */
    void modifyKey(int e, int newP);

    /*
     * @brief Metoda zwracająca rozmiar kopca
     * @return size_t - rozmiar kopca
     */
    size_t returnSize() const;

    /*
     * @brief Metoda sprawdzająca, czy kopiec jest poprawny
     * @return bool - true, jeśli kopiec jest poprawny, false w przeciwnym wypadku
     */
    void print() const;

    /*
     * @brief Metoda czyszcząca kopiec
     * @return void
     */
    void clearHeap();

    /*
     * @brief Metoda sprawdzająca, czy kopiec jest poprawny
     * @return bool - true, jeśli kopiec jest poprawny, false w przeciwnym wypadku
     */
    bool isHeapValid() const;
};

#endif