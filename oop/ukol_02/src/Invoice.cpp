#include "Invoice.h"

using namespace std;

Invoice::Invoice(int id, string jmeno, string prijmeni, string adresa)
{
    this->id = move(id);
    this->person = new Person(jmeno, prijmeni, adresa);
}

Invoice::~Invoice()
{
    delete this;
}

void Invoice::addItem(string name, double price)
{
    this->List->push_back(*new Item(name, price));
}

double Invoice::priceSum()
{
    double sum = 0;

    for (int i = 0; i < this->List->size(); i++)
    {
        sum += this->List->at(i).price;
    }

    return sum;
}