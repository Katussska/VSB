#include <iostream>
#include <string>

using namespace std;

class Person
{
private:
    string name;
    string surname;
    string address;

public:
    Person(string jmeno, string prijmeni, string adresa);
    void set_name(const string &jmeno);
    const string &get_name();
    void set_surname(const string &prijmeni);
    const string &get_surname();
    void set_address(const string &adresa);
    const string &get_address();
};
