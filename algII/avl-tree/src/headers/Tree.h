//
// Created by katussska on 10/5/23.
//

#ifndef AVL_TREE_TREE_H
#define AVL_TREE_TREE_H

using namespace std;

#include "Node.h"


class Tree {
public:
    Node *root;

    Tree();

    int getNodeHeight(Node *node);

    int balance(Node *node); //pro vybalancovani

    Node *rotateRight(Node *node); //rotace vpravo
    Node *rotateLeft(Node *node); //rotace vlevo
    Node *insert(Node *node, int key); //dopsat rotace

    //vypsani stromu
};


#endif //AVL_TREE_TREE_H
