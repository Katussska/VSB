//
// Created by katussska on 10/5/23.
//
#include <iostream>
#include <vector>
#include <queue>
#include "headers/Tree.h"

using namespace std;

int main() {

    vector<int> values = {15, 4, 8, 49, 20, 1, 0, 15, 36};
    Tree tree;

    for (int i = 0; i < values.size(); i++) {
        tree.root = tree.insert(tree.root, values.at(i));
    }


    return 0;
}

