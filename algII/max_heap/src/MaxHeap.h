//
// Created by katussska on 10/12/23.
//

#ifndef MAX_HEAP_MAXHEAP_H
#define MAX_HEAP_MAXHEAP_H

#include <iostream>
#include <vector>

using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    void heapifUp(int value);
    void heapiDown(int value);

public:
    void insert(int value);
    void remove(int value);
    void print();
};

#endif //MAX_HEAP_MAXHEAP_H
