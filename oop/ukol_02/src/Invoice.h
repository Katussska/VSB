#include "Person.h"
#include "Item.h"
#include <vector>

using namespace std;

class Invoice
{
private:
    int id;
    Person *person;
    vector<Item> *List;

public:
    Invoice(int id, string jmeno, string prijmeni, string adresa);
    ~Invoice();
    void addItem(string name, double price);
    double priceSum();
};
