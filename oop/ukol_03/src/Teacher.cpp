#include "Teacher.h"

Teacher::Teacher(string name, int salary)
{
    this->name = move(name);
    this->salary = salary;
}