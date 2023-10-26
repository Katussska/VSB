#include <iostream>
#include <vector>

class BTree {
private:
    // Struktura pro uzel B-stromu
    struct Node {
        bool isLeaf;          // Indikuje, zda je uzel listem
        std::vector<int> keys; // Seznam klíčů v uzlu
        std::vector<Node*> children; // Seznam potomků (pouze pokud uzel není list)
    };

    Node* root; // Kořenový uzel B-stromu
    int order;  // Řád B-stromu (maximální počet klíčů v uzlu)

    // Pomocné metody pro vkládání
    void insertNonFull(Node* node, int value); // Vložení do neplného uzlu
    void splitChild(Node* parent, int index);  // Rozdělení plného potomka
public:
    BTree(int order); // Konstruktor
    void insert(int value); // Hlavní metoda pro vkládání
};

// Konstruktor B-stromu
BTree::BTree(int order) {
    this->order = order;
    root = new Node;
    root->isLeaf = true;
}

// Hlavní metoda pro vkládání prvku do B-stromu
void BTree::insert(int value) {
    Node* r = root;

    // Pokud je kořen plný, vytvoříme nový kořen
    if (r->keys.size() == 2 * order - 1) {
        Node* newRoot = new Node;
        newRoot->isLeaf = false;
        newRoot->children.push_back(r);
        splitChild(newRoot, 0);
        root = newRoot;
    }

    // Vložíme prvek do stromu
    insertNonFull(root, value);
}

// Pomocná metoda pro vkládání do neplného uzlu
void BTree::insertNonFull(Node* node, int value) {
    int i = node->keys.size() - 1;

    if (node->isLeaf) {
        node->keys.push_back(0); // Přidání místa pro nový klíč
        while (i >= 0 && value < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = value;
    } else {
        while (i >= 0 && value < node->keys[i]) {
            --i;
        }
        ++i;
        if (node->children[i]->keys.size() == 2 * order - 1) {
            splitChild(node, i);
            if (value > node->keys[i]) {
                ++i;
            }
        }
        insertNonFull(node->children[i], value);
    }
}

// Pomocná metoda pro rozdělení plného potomka
void BTree::splitChild(Node* parent, int index) {
    Node* child = parent->children[index];
    Node* newChild = new Node;
    newChild->isLeaf = child->isLeaf;

    child->keys.resize(order - 1);
    newChild->keys.insert(newChild->keys.begin(), child->keys.begin() + order, child->keys.end());
    child->keys.pop_back();

    if (!child->isLeaf) {
        newChild->children.insert(newChild->children.begin(), child->children.begin() + order, child->children.end());
        child->children.resize(order);
    }

    parent->keys.insert(parent->keys.begin() + index, child->keys[order - 1]);
    parent->children.insert(parent->children.begin() + index + 1, newChild);
}

int main() {
    BTree btree(3);

    btree.insert(10);
    btree.insert(20);
    btree.insert(5);
    btree.insert(6);
    btree.insert(12);

    return 0;
}
