// Inheritance - dědičnost
// Inheritance hierarchy - dědičná hierarchie
// Inheritance extension - dědičné rozšíření / Change of behaviour - změna chování / Latened feedback - Pozdní vazba
// Abstract class - abstraktní třída
// Polymorphism - polymorfismus (datová struktura i přiřazení)
#ifndef OOPZOO_EMPLOYEE_H
#define OOPZOO_EMPLOYEE_H

#include <iostream>
#include <string>
#include "Animal.h"
#include "Habitat.h"
using namespace std;

class Work {
public:
    virtual void doWork() = 0; // each employee will have its own implementation
};

class Employee : public Work {
public:
    Employee(string name, double salary);
    string getEmployeeName();
    double getEmployeeSalary();
    void increaseEmployeeSalary(double increase);
    virtual void doWork() = 0;

private:
    string name;
    double salary;
};

class Curator : public Employee {
public:
    Curator(string name, double salary, string department);
    string getDepartment();
    void doWork();
    void doWork(Animal*); // implement doWork for Curator

private:
    string department;
};

class Cleaner : public Employee {
public:
    Cleaner(string name, double salary, string cleaningArea);
    string getCleaningArea();
    void doWork();
    void doWork(Habitat*); // implement doWork for Cleaner

private:
    string cleaningArea;
};

class Feeder : public Employee {
public:
    Feeder(string name, double salary, string feedingArea);
    string getFeedingArea();
    void doWork();
    void doWork(Animal*); // implement doWork for Feeder

private:
    string feedingArea;
};

class Seller : public Employee {
public:
    Seller(string name, double salary, string shop);
    string getShop();
    void doWork(); // implement doWork for Seller

private:
    string shop;
};

class MammalExpert : public Curator {
public:
    MammalExpert(string name, double salary, string department, string expertise);
    void trainMammals();
private:
    string expertise;
};

class BackupCurator : public Curator {
public:
    BackupCurator(string name, double salary, string department, string favAnimal) : Curator(name, salary, department), favAnimal(favAnimal) {}
    string getFavAnimal() { return favAnimal; }
    void doWork() override {
        cout << "Backup curator " << getEmployeeName() << " is filling in for the curator of the " << getDepartment() << " department and is now training " << getFavAnimal() << "." << endl;
    }
private:
    string favAnimal;
};

class Veterinarian : public Employee {
public:
    Veterinarian(string name, double salary, string clinic);
    string getClinic();
    void doWork();
    void doWork(Animal*); // implement doWork for Cleaner

private:
    string clinic;
};

#endif //OOPZOO_EMPLOYEE_H
