#include "Person.h"

using namespace std;

Person::Person(string jmeno, string prijmeni, string adresa)
{
    this->name = move(jmeno);
    this->surname = move(prijmeni);
    this->address = move(adresa);
}

void Person::set_name(const string &jmeno)
{
    name = jmeno;
}

const string &Person::get_name()
{
    return name;
}

void Person::set_surname(const string &prijmeni)
{
    surname = prijmeni;
}

const string &Person::get_surname()
{
    return surname;
}

void Person::set_address(const string &adresa)
{
    address = adresa;
}

const string &Person::get_address()
{
    return address;
}