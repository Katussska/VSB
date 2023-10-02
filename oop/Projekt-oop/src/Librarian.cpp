#include "headers/User.h"

Librarian::Librarian(std::string name, std::string adress, int empId, double salary)
    : User(name, adress) // hierarchie (librarian z usera, to samé registered user)
{
    this->employeeId = empId;
    this->salary = salary;
}

Librarian::~Librarian()
{
}

void Librarian::setEmployeeId(int id)
{
    this->employeeId = id;
}

void Librarian::setSalary(double salary)
{
    this->salary = salary;
}

int Librarian::getEmployeeId()
{
    return employeeId;
}

double Librarian::getSalary()
{
    return salary;
}

void Librarian::addMoney(double amount)
{
    std::cout << "Aktuální plat " << this->getName() << ": " << this->getSalary() << std::endl;
    this->salary += amount;
    std::cout << "Plat po přidání: " << this->getSalary() << std::endl;
}