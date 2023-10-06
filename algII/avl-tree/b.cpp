//
// Created by katussska on 10/5/23.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
    int key;          // Klíč uzlu, který reprezentuje hodnotu v uzlu.
    Node *left;       // Ukazatel na levého potomka uzlu.
    Node *right;      // Ukazatel na pravého potomka uzlu.
    int height;       // Výška uzlu v AVL sidentifiertromu.

    // Konstruktor uzlu, který inicializuje klíč na zadanou hodnotu a
    // nastavuje ukazatele na potomky na nullptr. Výška uzlu je nastavena na 1.
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};


class AVLTree {
public:
    Node *root;

    // Konstruktor AVL stromu. Inicializuje kořen stromu na nullptr.
    AVLTree() : root(nullptr) {}

    // Metoda pro získání výšky uzlu v rámci AVL stromu.
    int height(Node *node) {
        if (node == nullptr) {
            return 0;
        }

        return node->height; // Vrátíme výšku uzlu.
    }

    // Metoda pro výpočet vyvážení uzlu, což je rozdíl výšek levého a pravého podstromu.
    int balanceFactor(Node *node) {
        if (node == nullptr) {
            return 0;
        }

        // Vrátíme rozdíl výšek levého a pravého podstromu
        return height(node->left) - height(node->right);
    }

    // Rotace po směru hodinových ručiček (pravá rotace)
    Node *rotateRight(Node *y) {

        // Uložení levého potomka uzlu y do nového uzlu x
        Node *x = y->left;

        // Uložení pravého potomka (podstromu) uzlu x do T2
        Node *T2 = x->right;

        // Provádíme rotaci:
        // 1. Přesměrování pravého potomka uzlu x na y
        x->right = y;
        // 2. Přesměrování levého potomka uzlu y na T2
        y->left = T2;

        // Aktualizace výšek uzlů po rotaci.
        // Výška uzlu y je maximem výšek jeho levého a pravého podstromu, zvýšíme o 1
        y->height = max(height(y->left), height(y->right)) + 1;
        // Výška uzlu x je maximem výšek jeho levého a pravého podstromu, zvýšíme o 1
        x->height = max(height(x->left), height(x->right)) + 1;

        return x; // Vracíme nový kořen (uzel x) po rotaci
    }


    // Rotace proti hodinovým ručičkám (levá rotace).
    Node *rotateLeft(Node *x) {

        // Uložíme pravého potomka uzlu x do y
        Node *y = x->right;

        // Uložíme levého potomka uzlu y do T2.
        Node *T2 = y->left;

        // Provádíme rotaci:
        // 1. Přesměrování levého potomka uzlu y na x
        y->left = x;
        // 2. Přesměrování pravého potomka uzlu x na T2
        x->right = T2;

        // Aktualizace výšek uzlů po rotaci.
        // Výška uzlu x je maximem výšek jeho levého a pravého podstromu, zvýšíme o 1
        x->height = max(height(x->left), height(x->right)) + 1;
        // Výška uzlu y je maximem výšek jeho levého a pravého podstromu, zvýšíme o 1
        y->height = max(height(y->left), height(y->right)) + 1;

        // Vracíme nový kořen (uzel y) po rotaci
        return y;
    }


    // Vložení prvku do stromu
    Node *insert(Node *node, int key) {
        // Pokud je uzel prázdný, vytvoříme nový uzel s daným klíčem.
        if (node == nullptr) {
            return new Node(key);
        }

        // Porovnáme klíč s klíčem aktuálního uzlu a rozhodneme, do kterého podstromu vložit.
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node; // Duplicitní klíč, uzel již existuje, neprovádíme vkládání.
        }

        // Aktualizace výšky tohoto uzlu po vložení potomka.
        node->height = 1 + max(height(node->left), height(node->right));

        // Zkontrolujeme vyvážení a provedeme rotace, pokud je třeba.

        int balance = balanceFactor(node);

        // LL rotace
        // Když se vyvážení uzlu stane větším než 1 a problém je v levém podstromu uzlu a ještě více v levém podstromu tohoto levého uzlu.
        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }


        // RR rotace
        // Když se vyvážení uzlu stane menším než -1 a problém je v pravém podstromu uzlu a ještě více v pravém podstromu tohoto pravého uzlu.
        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }


        // LR rotace
        // Když se vyvážení uzlu stane větším než 1 a problém je v levém podstromu uzlu, ale více v pravém podstromu tohoto levého uzlu.
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RL rotace
        // Když se vyvážení uzlu stane menším než -1 a problém je v pravém podstromu uzlu, ale více v levém podstromu tohoto pravého uzlu.
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // In-order průchod stromem (výpis)
    void inOrderTraversal(Node *node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->key << " ";
            inOrderTraversal(node->right);
        }
    }

    void printTreeLevelOrder() {
        // Pokud je kořen stromu nullptr, strom je prázdný, a není co vypisovat.
        if (root == nullptr) {
            return;
        }

        // Vytvoření fronty pro uchování uzlů stromu.
        queue<Node *> q;

        // Vložení kořene stromu do fronty.
        q.push(root);

        // Vložení nullptr jako oddělovače úrovní.
        q.push(nullptr); // Oddělovač úrovní

        // Hlavní smyčka pro průchod stromem úroveň po úrovni.
        while (!q.empty()) {
            // Získání aktuálního uzlu z fronty.
            Node *current = q.front();
            q.pop();

            // Pokud aktuální uzel je nullptr, dosáhli jsme konce úrovně.
            if (current == nullptr) {
                // Vytiskneme nový řádek, aby byly uzly jednotlivých úrovní odděleny.
                cout << endl;

                // Pokud fronta není prázdná (další úroveň uzlů), přidáme další nullptr jako oddělovač úrovní.
                if (!q.empty()) {
                    q.push(nullptr);
                }
            } else {
                // Vypíšeme hodnotu aktuálního uzlu, oddělenou mezerou.
                cout << current->key << " ";

                // Pokud má aktuální uzel levého potomka, přidáme ho do fronty.
                if (current->left != nullptr) {
                    q.push(current->left);
                }

                // Pokud má aktuální uzel pravého potomka, přidáme ho do fronty.
                if (current->right != nullptr) {
                    q.push(current->right);
                }
            }
        }
    }
};

int main() {
    vector<int> avlVector = {20, 10, 5, 13, 18, 25, 26, 27, 28, 12};
    AVLTree avlTree;

    for (int key: avlVector) {
        avlTree.root = avlTree.insert(avlTree.root, key);
    }

    cout << "Serazeny vypis: " << endl;
    avlTree.inOrderTraversal(avlTree.root);
    cout << endl << endl;

    cout << "Serazeny vypis odshora dolu po radcich: " << endl;
    avlTree.printTreeLevelOrder();
    cout << endl;


    return 0;
}
