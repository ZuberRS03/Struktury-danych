#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <queue>

class MaxHeap {
private:
    std::priority_queue<int> pq;

public:
    void insert(int element);
    int findMax();
    void removeMax();
    bool isEmpty();
};

#endif