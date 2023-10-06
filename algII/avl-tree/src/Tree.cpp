//
// Created by katussska on 10/5/23.
//

#include "headers/Tree.h"

Tree::Tree() {
    this->root = nullptr;
}

int Tree::getNodeHeight(Node *node) {
    if (node == nullptr)
        return 0;

    return node->height;
}

int Tree::balance(Node *node) {

}

Node *Tree::rotateRight(Node *node) {

}

Node *Tree::rotateLeft(Node *node) {

}

Node *Tree::insert(Node *node, int key) {
    if (node == nullptr)
        return new Node(key); //pokud je uzel prazdny, vytvori se novy

    if (key < node->key) //hodnota mensi, prida se doleva
        node->left = insert(node->left, key);
    else if (key > node->key) // hodnota vetsi, prida se doprava
        node->right = insert(node->right, key);
    else //duplikat, no insert
        return node;
    
    //dopsat rotace
}