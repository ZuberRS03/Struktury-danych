#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class MaxHeap {
private:
    std::vector<std::pair<int, int>> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);
    int findIndex(int e);

public:
    void insert(int e, int p);
    std::pair<int, int> extractMax();
    std::pair<int, int> findMax() const;
    void modifyKey(int e, int newP);
    size_t returnSize() const;
    void print() const;
    void clearHeap();
    bool isHeapValid() const;
};

#endif