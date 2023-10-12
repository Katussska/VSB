//
// Created by katussska on 10/12/23.
//
#include "MaxHeap.h"

using namespace std;

int main() {
    MaxHeap maxHeap;
    vector<int> values = {3, 8, 12, 15, 16, 19, 28, 32};

    for (int value: values)
        maxHeap.insert(value);

    cout << "Max Heap: ";
    maxHeap.print();

    maxHeap.remove(10);
    maxHeap.remove(19);

    cout << "Max Heap after removing: ";
    maxHeap.print();

    return 0;
}

