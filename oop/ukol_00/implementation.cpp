#include "declaration.h"
#include <utility>

using namespace std;

osoba::osoba(string jmeno, string prijmeni, int vek)
{
    this->name = move(jmeno);
    this->surname = move(prijmeni);
    this->age = vek;
}

void osoba::set_name(const string &jmeno)
{
    name = jmeno;
}

const string &osoba::get_name()
{
    return name;
}

void osoba::set_surname(const string &prijmeni)
{
    surname = prijmeni;
}

const string &osoba::get_surname()
{
    return surname;
}

void osoba::set_age(int vek)
{
    age = vek;
}

email::email(string jmeno, string domena, string heslo)
{
    this->username = move(jmeno);
    this->domainName = move(domena);
    this->password = move(heslo);
}

void email::set_username(const string &jmeno)
{
    username = jmeno;
}

const string &email::get_username()
{
    return username;
}

void email::set_domainName(const string &domena)
{
    domainName = domena;
}

const string &email::get_domainName()
{
    return domainName;
}

void email::set_password(const string &heslo)
{
    password = heslo;
}
