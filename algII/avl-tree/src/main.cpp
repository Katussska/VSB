//
// Created by katussska on 10/5/23.
//
#include "headers/Tree.h"

using namespace std;

int main() {

    vector<int> values = {3, 8, 12, 15, 16, 19, 28, 32, 45, 50, 56, 61, 62, 64, 66, 77, 85, 86, 87, 88};
    Tree tree;

    for (int i = 0; i < values.size(); i++) {
        tree.root = tree.insert(tree.root, values.at(i));
    }

    cout << "Printed tree: " << endl;
    tree.printTree(tree.root, 3);
    cout << endl;

    return 0;
}

