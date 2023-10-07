//
// Created by katussska on 10/5/23.
//

#ifndef AVL_TREE_TREE_H
#define AVL_TREE_TREE_H

#include "Node.h"


class Tree {
public:
    Node *root;

    Tree();

    int getNodeHeight(Node *node);

    int isBalanced(Node *node); //pro vybalancovani

    Node *rightRotation(Node *node); //rotace vpravo
    Node *leftRotation(Node *node); //rotace vlevo
    Node *insert(Node *node, int key); //dopsat rotace

    void printTree(Node *root, int space);
};


#endif //AVL_TREE_TREE_H
