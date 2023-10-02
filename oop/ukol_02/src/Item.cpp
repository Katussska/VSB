#include "Item.h"

using namespace std;

Item::Item(string name, double price)
{
    this->name = move(name);
    this->price = move(price);
}

Item::~Item()
{
    delete this;
}