//
// Created by katussska on 10/12/23.
//

#include "MaxHeap.h"
#include <bits/stdc++.h>

void MaxHeap::heapifUp(int index) {
    int parent = (index - 1) / 2;
    if (index > 0 && heap[index] > heap[parent]) {
        swap(heap[index], heap[parent]);
        heapifUp(parent);
    }
}

void MaxHeap::heapiDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
        largest = leftChild;
    }

    if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
        largest = rightChild;
    }

    if (largest != index) {
        swap(heap[index], heap[largest]);
        heapiDown(largest);
    }
}

void MaxHeap::insert(int value) {
    heap.push_back(value);
    heapifUp(heap.size() - 1);
}

void MaxHeap::remove(int value) {
    auto it = find(heap.begin(), heap.end(), value);

    if (it == heap.end()) {
        cout << "Element " << value << " not found in the heap." << endl;
        return;
    }

    int index = distance(heap.begin(), it);
    swap(heap[index], heap[heap.size() - 1]);
    heap.pop_back();

    if (index < heap.size()) {
        heapifUp(index);
        heapiDown(index);
    }
}

void MaxHeap::print() {
    if (heap.empty()) {
        cout << "Heap is empty." << endl;
        return;
    }

    for (int i : heap)
        cout << i << " ";

    cout << endl;
}