#include <string>

using namespace std;

#ifndef INC_UKOL_01_DECLARATION_H
#define INC_UKOL_01_DECLARATION_H

class osoba
{
private:
    string name;
    string surname;
    int age;

public:
    osoba(string jmeno, string prijmeni, int vek);
    void set_name(const string &jmeno);
    const string &get_name();
    void set_surname(const string &prijmeni);
    const string &get_surname();
    void set_age(int vek);
};

class email
{
private:
    string username;
    string domainName;
    string password;

public:
    email(string jmeno, string domena, string heslo);
    void set_username(const string &jmeno);
    const string &get_username();
    void set_domainName(const string &domena);
    const string &get_domainName();
    void set_password(const string &heslo);
};

#endif // INC_UKOL_01_DECLARATION_H