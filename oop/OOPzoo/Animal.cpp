#include "Animal.h"

string Animal::getName() const { return name; }
char Animal::getSex() const { return sex; }
string Animal::getSpecies() const { return species; }
string Animal::getParent1() const { return parent1; }
string Animal::getParent2() const { return parent2; }
int Animal::getHealth() const { return health; }
int Animal::getHappiness() const { return happiness; }
int Animal::getHunger() const { return hunger; }

void Animal::setName(string name) { this->name = name; }
void Animal::setSex(char sex) { this->sex = sex; }
void Animal::setSpecies(string species) { this->species = species; }
void Animal::setParent1(string parent1) { this->parent1 = parent1; }
void Animal::setParent2(string parent2) { this->parent2 = parent2; }
void Animal::setHealth(int health) { this->health = health; }
void Animal::setHappiness(int happiness) { this->happiness = happiness; }
void Animal::setHunger(int hunger) { this->hunger = hunger; }
void Animal::feed() {
    hunger += 5;
    if (hunger < 0) {
        hunger = 0;
    }
}
