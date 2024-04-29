#include "MaxHeap.h"
#include <stdexcept>  // Include to use std::runtime_error

void MaxHeap::insert(int element) {
    // Adds an element to the heap; priority_queue will automatically order it in max-heap order
    pq.push(element);
}

int MaxHeap::findMax() {
    // Returns the largest element from the heap without removing it
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty"); 
    }
    return pq.top();
}

void MaxHeap::removeMax() {
    // Removes the largest element from the heap; priority_queue will automatically reorder
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty"); 
    }
    pq.pop();
}

bool MaxHeap::isEmpty() {
    // Checks if the heap is empty
    return pq.empty();
}