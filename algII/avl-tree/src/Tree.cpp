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

int Tree::isBalanced(Node *node) {
    if (node == nullptr)
        return 0;
    //vratime rozdil vysek leveho a praveho odvetvi
    return getNodeHeight(node->left) - getNodeHeight(node->right);
}

Node *Tree::rightRotation(Node *nodeR) {
    //ulozeni leveho potomka uzlu node do nového uzlu nodeL
    Node *nodeL = nodeR->left;
    //ulozeni praveho potomka odvetvi uzlu nodeL do temp
    Node *temp = nodeL->right;

    //presmerovani praveho potomka uzlu nodeL na nodeR
    nodeL->right = nodeR;
    //presmerovani leveho potomka uzlu nodeR na temp
    nodeR->left = temp;

    //vyska uzlu nodeR je maximem vysek jeho leveho a praveho podstromu
    //zvysime o 1
    nodeR->height = max(getNodeHeight(nodeR->left), getNodeHeight(nodeR->right)) + 1;
    //vyska uzlu nodeL je maximem vysek jeho leveho a praveho podstromu
    //zvysime o 1
    nodeL->height = max(getNodeHeight(nodeL->left), getNodeHeight(nodeL->right)) + 1;

    //vracime novy koren, uzel nodeL, po rotaci
    return nodeL;
}

Node *Tree::leftRotation(Node *nodeL) {
    //ulozeni praveho potomka uzlu nodeL do nodeR
    Node *nodeR = nodeL->right;

    //ulozeni leveho potomka uzlu nodeR do temp.
    Node *temp = nodeR->left;


    //presmerovani leveho potomka uzlu nodeR na nodeL
    nodeR->left = nodeL;
    //presmerovani praveho potomka uzlu nodeL na temp
    nodeL->right = temp;

    //vyska uzlu nodeL je maximem vysek jeho leveho a praveho podstromu
    //zvysime o 1
    nodeL->height = max(getNodeHeight(nodeL->left), getNodeHeight(nodeL->right)) + 1;
    //vyska uzlu nodeR je maximem vysek jeho leveho a praveho podstromu
    //zvysime o 1
    nodeR->height = max(getNodeHeight(nodeR->left), getNodeHeight(nodeR->right)) + 1;

    //vracime novy koren, uzel nodeR, po rotaci
    return nodeR;
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

    //aktualizace vysky uzlu
    node->height = 1 + max(getNodeHeight(node->left), getNodeHeight(node->right));

    //kontrola vyvazeni kvuli rotacim
    int balance = isBalanced(node);

    //LL rotace
    //pokud isBalanced > 1 && problem je v levem odvetvi a i dale vlevo
    if (balance > 1 && key < node->left->key)
        return rightRotation(node);

    //RR rotace
    //pokud isBalanced < -1 && problem je v pravem odvetvi a i dale vpravo
    if (balance < -1 && key > node->right->key)
        return leftRotation(node);


    //LR rotace
    //pokud isBalanced > 1 && problem je v levem odvetvi, ale vice vpravo
    // Když se vyvážení uzlu stane větším než 1 a problém je v levém podstromu uzlu, ale více v pravém podstromu tohoto levého uzlu.
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    //RL rotace
    //pokud isBalanced < -1 && problem je v pravem odvetvi, ale vice vlevo
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}

void Tree::printTree(Node *root, int space) {
    if (root == nullptr)
        return;

    const int distance = 4; //distance zleva doprava, space nahoru dolu
    space += distance;

    if (root->right != nullptr)
        printTree(root->right, space);

    cout << endl;
    for (int i = distance; i < space; i++)
        cout << " ";
    cout << root->key << endl;

    if (root->left != nullptr)
        printTree(root->left, space);
}
