// Overloading - přetížení (Animal konstruktor)
#ifndef OOPZOO_ANIMAL_H
#define OOPZOO_ANIMAL_H

#include <iostream>
using namespace std;

class Animal {
public:
    Animal(string name, char sex, string species, int health = 0, int happiness = 0, int hunger = 0) // nemá / nevíme rodiče
            : name(name), sex(sex), species(species), parent1("N"), parent2("N"), health(health), happiness(happiness), hunger(hunger) {}

    Animal(string name, char sex, string species, string parent1, string parent2) // víme rodiče
            : name(name), sex(sex), species(species), parent1(parent1), parent2(parent2), health(0), happiness(0), hunger(0) {}

    ~Animal() {}

    string getName() const;
    char getSex() const;
    string getSpecies() const;
    string getParent1() const;
    string getParent2() const;
    int getHealth() const;
    int getHappiness() const;
    int getHunger() const;

    void setName(string name);
    void setSex(char sex);
    void setSpecies(string species);
    void setParent1(string parent1);
    void setParent2(string parent2);
    void setHealth(int health);
    void setHappiness(int happiness);
    void setHunger(int hunger);

    virtual void feed();

private:
    string name;
    char sex;
    string species;
    string parent1;
    string parent2;
    int health;
    int happiness;
    int hunger;
};


#endif //OOPZOO_ANIMAL_H
