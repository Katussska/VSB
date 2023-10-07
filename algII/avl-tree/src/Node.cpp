//
// Created by katussska on 10/5/23.
//

#include "headers/Node.h"

using namespace std;

Node::Node(int key) {
    this->key = key;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}
