#include <string>
#include "Tree.h"

using namespace std;

Tree::Tree(string k, string v, int depth)
{
    this->key = k;
    this->value = v;
    this->depth = depth;
    this->nextY = nullptr;
    this->nextN = nullptr;
}

Tree::~Tree()
{
    if (this->nextY != nullptr)
    {
        delete this->nextY;
        this->nextY = nullptr;
    }
    if (this->nextN != nullptr)
    {
        delete this->nextN;
        this->nextN = nullptr;
    }
}
string Tree::GetKey()
{
    return this->key;
}

string Tree::GetValue()
{
    return this->value;
}

int Tree::GetDepth()
{
    return this->depth;
}
Tree *Tree::GetNext(char side)
{
    if (side == 'y')
    {
        return this->nextY;
    }

    if (side == 'n')
    {
        return this->nextN;
    }

    return nullptr;
}
Tree *Tree::CreateNext(std::string k, std::string v, char side)
{
    if (side == 'y')
    {
        this->nextY = new Tree(k, v, this->depth + 1);
        return this->nextY;
    }

    if (side == 'n')
    {
        this->nextN = new Tree(k, v, this->depth + 1);
        return this->nextN;
    }

    return nullptr;
}
