#include <iostream>
#include "Animal.h"
#include "Habitat.h"
#include "Employee.h"
#include "Pavilion.h"

using namespace std;

int main() {
    // PROJEKT
    // Kompozice
    /*Pavilion aquarium("Aquarium");
    Habitat coralReef("Coral Reef", 100, 50);
    Habitat kelpForest("Kelp Forest", 200, 100);
    aquarium.addHabitat(&coralReef);
    aquarium.addHabitat(&kelpForest);

     // Polymorfismus struktura (dole delete pro employees)
    Employee* employee1 = new Curator("John", 5000.0, "Reptile");
    Employee* employee2 = new Cleaner("Anna", 2000.0, "Aquarium");
    Work* work1 = employee1;
    Work* work2 = employee2;
    work1->doWork(); // curator doWork()
    work2->doWork(); // cleaner doWork()

    // Polymorfismus - assignment
    Employee* emp1 = new Curator("John Doe", 2000.0, "Aquarium");
    Employee* emp2 = new Cleaner("Jane Smith", 1500.0, "Lion's den");
    emp1->doWork(); // curator doWork()
    emp2->doWork(); // cleaner doWork()*/









    // Actual ukázka
    // Creating pavilions and habitats, then putting those habitats into pavilions
    Pavilion aquarium("Aquarium");
    Habitat coralReef("Coral Reef", 100, 50);
    Habitat kelpForest("Kelp Forest", 200, 100);
    aquarium.addHabitat(&coralReef);
    aquarium.addHabitat(&kelpForest);

    Pavilion africa("Africa");
    Habitat savanna("Savanna", 80, 50);
    Habitat desert("Desert", 50, 100);
    africa.addHabitat(&coralReef);
    africa.addHabitat(&kelpForest);


    // Creating employees
    vector<Employee*> employees;
    Curator* curator1 = new Curator("Radek Rubina", 40000, "Fish");
    Employee* curator2 = new Curator("John", 5000, "Reptile");
    Cleaner* cleaner1 = new Cleaner("Radek Čubina", 25000, "Savanna");
    Cleaner* cleaner2 = new Cleaner("Radek Dubina", 25000, "Fish");
    Feeder* feeder1 = new Feeder("Radek Kubina", 30000, "Savanna");
    Feeder* feeder2 = new Feeder("Radek Mubina", 30000, "Coral Reef");
    Seller* seller1 = new Seller("Radek Zubina", 35000, "Food stands");
    employees.push_back(curator1);
    employees.push_back(curator2);
    employees.push_back(cleaner1);
    employees.push_back(cleaner2);
    employees.push_back(feeder1);
    employees.push_back(feeder2);
    employees.push_back(seller1);


    // Demonstrating some getter and setters from the Employee class
    cout << "Fish curator name: " << curator1->getEmployeeName() << endl;
    cout << "Fish curator salary: " << curator1->getEmployeeSalary() << endl;
    curator1->increaseEmployeeSalary(2000);
    cout << "Fish curator salary: " << curator1->getEmployeeSalary() << endl;


    // Creating animals and putting them into habitats
    Animal* animal1 = new Animal("Tonda", 'M', "Lion", 50, 60, 70);
    Animal* animal2 = new Animal("Kvetoslava", 'F', "Lion", 50, 60, 70);
    Animal* animal3 = new Animal("Tonda Jr.", 'M', "Lion", "Tonda", "Kvetoslava");
    Animal* animal4 = new Animal("Ludmila", 'F', "Lion", "Tonda", "Kvetoslava");
    Animal* animal5 = new Animal("Spytihnev", 'M', "Camel", 10, 5, 5);
    Animal* animal6 = new Animal("Libuse", 'F', "Camel", 20, 70, 90);
    Animal* animal7 = new Animal("Roman", 'M', "Camel", "Spytihnev", "Libuse");
    Animal* animal8 = new Animal("Svatopluk", 'M', "Camel", "Spytihnev", "Libuse");
    Animal* animal9 = new Animal("Martin", 'M', "Beta fish", 0, 0, 0);
    Animal* animal10 = new Animal("Dalibor", 'M', "Beta fish", 50, 20, 30);
    Animal* animal11 = new Animal("Keanu", 'M', "Beta fish", 90, 80, 50);
    Animal* animal12 = new Animal("Dezo", 'M', "Beta fish", 50, 50, 50);
    savanna.addAnimal(animal1);
    savanna.addAnimal(animal2);
    savanna.addAnimal(animal3);
    savanna.addAnimal(animal4);
    desert.addAnimal(animal5);
    desert.addAnimal(animal6);
    desert.addAnimal(animal7);
    desert.addAnimal(animal8);
    coralReef.addAnimal(animal9);
    coralReef.addAnimal(animal10);
    coralReef.addAnimal(animal11);
    coralReef.addAnimal(animal12);


    // Demonstrating removing animal from a habitat, some getter and setters from the Animal and Habitat classes
    vector<Animal *> animals = savanna.getAnimals();
    cout << "Number of animals in the savanna: " << savanna.getNumAnimals() << endl;
    for (int i = 0; i < animals.size(); i++) {
        cout << "Names of the savanna animals: " << animals[i]->getName() << endl;
    }
    savanna.removeAnimal("Tonda");
    animals = savanna.getAnimals();
    cout << "Number of animals in the savanna: " << savanna.getNumAnimals() << endl;
    for (int i = 0; i < animals.size(); i++) {
        cout << "Names of the savanna animals: " << animals[i]->getName() << endl;
    }
    cout << "Size of the savanna: " << savanna.getWidthX() << " " << savanna.getWidthY() << endl;
    savanna.setWidthX(50);
    cout << "Size of the savanna: " << savanna.getWidthX() << " " << savanna.getWidthY() << endl;


    // Employees working - interacting with animals
    cout << animal6->getName() << "happiness (before): " << animal6->getHappiness() << endl;
    curator1->doWork(animal6);
    cout << animal6->getName() << "happiness (after): " << animal6->getHappiness() << endl;
    cout << "Coral Reef cleanliness (before): " << coralReef.getCleanliness() << endl;
    cleaner1->doWork(&coralReef);
    cout << "Coral Reef cleanliness (after): " << coralReef.getCleanliness() << endl;


    // Backup curator and mammal expert
    BackupCurator* backupcurator = new BackupCurator("Radek Hubina", 40000, "Africa", "Libuse");
    backupcurator->doWork();
    MammalExpert* mammalexpert = new MammalExpert("Radek Rubina", 40000, "Africa", "jumping");
    mammalexpert->trainMammals();


    // Deleting
    delete curator1;
    delete curator2;
    delete feeder1;
    delete feeder2;
    delete cleaner1;
    delete cleaner2;
    delete seller1;
    delete backupcurator;
    delete mammalexpert;
    delete animal1;
    delete animal2;
    delete animal3;
    delete animal4;
    delete animal5;
    delete animal6;
    delete animal7;
    delete animal8;
    delete animal9;
    delete animal10;
    delete animal11;
    delete animal12;










    // OOP CVIKO 2
    /*vector<Employee*> myemployees;
    Curator* c = new Curator("Jan Novak", 40000, "Mammals");
    Cleaner* cl = new Cleaner("Tomas Jedno", 25000, "Savanna");
    Feeder* f = new Feeder("Anna Pravacka", 30000, "Lions");
    Seller* s = new Seller("Petr Adam", 35000, "Food stands");
    myemployees.push_back(c);
    myemployees.push_back(cl);
    myemployees.push_back(f);
    myemployees.push_back(s);

    cout << "\n\n\n" << endl;
    for (int i = 0; i < myemployees.size(); i++) {
        cout << myemployees[i]->getEmployeeName() << ": " << myemployees[i]->getEmployeeSalary() << endl;
    }

    for (int i = 0; i < myemployees.size(); i++) { //vic money
        myemployees[i]->increaseEmployeeSalary(5000);
    }

    cout << "\n\n\n" << endl;
    for (int i = 0; i < myemployees.size(); i++) { // znova money
        cout << myemployees[i]->getEmployeeName() << ": " << myemployees[i]->getEmployeeSalary() << endl;
    }


    for (int i = 0; i < myemployees.size(); i++) {
        delete myemployees[i];
    }
    /*delete employee1; // K PROJEKTU polymorfismus - struktura
    delete employee2;*/

    return 0;
}