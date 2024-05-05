#include "MaxHeap.h"

void MaxHeap::insert(int e, int p) {
    heap.push_back({e, p});
    heapifyUp(heap.size() - 1);
}

std::pair<int, int> MaxHeap::extractMax() {
    if (heap.empty()) throw std::runtime_error("Heap is empty");
    std::swap(heap[0], heap.back());
    auto maxElement = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return maxElement;
}

std::pair<int, int> MaxHeap::findMax() const {
    if (heap.empty()) throw std::runtime_error("Heap is empty");
    return heap[0];
}

void MaxHeap::modifyKey(int e, int newP) {
    int index = findIndex(e);
    if (index == -1) throw std::runtime_error("Element not found");
    heap[index].second = newP;
    heapifyUp(index);
    heapifyDown(index);
}

size_t MaxHeap::returnSize() const {
    return heap.size();
}

void MaxHeap::heapifyUp(int index) {
    while (index > 0 && heap[index].second > heap[(index - 1) / 2].second) {
        std::swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void MaxHeap::heapifyDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    if (left < heap.size() && heap[left].second > heap[largest].second) {
        largest = left;
    }
    if (right < heap.size() && heap[right].second > heap[largest].second) {
        largest = right;
    }
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

int MaxHeap::findIndex(int e) {
    for (int i = 0; i < heap.size(); i++) {
        if (heap[i].first == e) return i;
    }
    return -1;
}

void MaxHeap::print() const {
    for (const auto& elem : heap) {
        std::cout << elem.first << " " << elem.second << std::endl;
    }
}

void MaxHeap::clearHeap() {
    heap.clear();
}