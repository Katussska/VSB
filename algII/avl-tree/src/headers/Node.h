//
// Created by katussska on 10/5/23.
//

#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
    int key; //klic uzlu(hodnota)
    int height; //vyska ve strome(pro rotaci)
    Node *left; //levy potomek
    Node *right; //pravy potomek

    explicit Node(int key);

};


#endif //AVL_TREE_NODE_H
