#include "Employee.h"
using namespace std;

Employee::Employee(string name, double salary) : name(name), salary(salary) {}
string Employee::getEmployeeName() { return name; }
double Employee::getEmployeeSalary() { return salary; }
void Employee::increaseEmployeeSalary(double increase) { salary += increase; }

Curator::Curator(string name, double salary, string department) : Employee(name, salary), department(department) {}
string Curator::getDepartment() { return department; }

Cleaner::Cleaner(string name, double salary, string cleaningArea) : Employee(name, salary), cleaningArea(cleaningArea) {}
string Cleaner::getCleaningArea() { return cleaningArea; }

Feeder::Feeder(string name, double salary, string feedingArea) : Employee(name, salary), feedingArea(feedingArea) {}
string Feeder::getFeedingArea() { return feedingArea; }

Seller::Seller(string name, double salary, string shop) : Employee(name, salary), shop(shop) {}
string Seller::getShop() { return shop; }

MammalExpert::MammalExpert(string name, double salary, string department, string expertise) : Curator(name, salary, department), expertise(expertise) {}
void MammalExpert::trainMammals() {
    cout << "Training mammals in " << expertise << " at " << getDepartment() << endl;
}

Veterinarian::Veterinarian(string name, double salary, string clinic) : Employee(name, salary), clinic(clinic) {}
string Veterinarian::getClinic() { return clinic; }

void Curator::doWork(Animal* animal) {
    animal->setHappiness(animal->getHappiness() + 5);
}

void Feeder::doWork(Animal* animal) {
    animal->setHunger(animal->getHunger() + 5);
}

void Cleaner::doWork(Habitat* habitat) {
    habitat->setCleanliness(habitat->getCleanliness() + 5);
}

void Veterinarian::doWork(Animal* animal) {
    animal->setHealth(animal->getHealth() + 5);
}

void Curator::doWork() {

}

void Feeder::doWork() {

}

void Cleaner::doWork() {

}

void Veterinarian::doWork() {

}

void Seller::doWork() {

}