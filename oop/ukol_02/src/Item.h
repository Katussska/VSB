#include <iostream>
#include <string>

using namespace std;

class Item
{
public:
    string name;
    double price;
    Item(string name, double price);
    ~Item();
};
