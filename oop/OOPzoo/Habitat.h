#ifndef OOPZOO_HABITAT_H
#define OOPZOO_HABITAT_H

#include <iostream>
#include <vector>
#include "Animal.h"

using namespace std;

class Habitat {
public:
    Habitat(string habitatType = "N", int widthX = 0, int widthY = 0, int cleanliness = 0)
            : habitatType(habitatType), widthX(widthX), widthY(widthY), numAnimals(0), cleanliness(cleanliness) {}

    ~Habitat() {}

    string getHabitatType() const;
    int getWidthX() const;
    int getWidthY() const;
    int getNumAnimals() const;
    vector<Animal*> getAnimals() const;
    int getCleanliness() const;

    void setHabitatType(string habitatType);
    void setWidthX(int widthX);
    void setWidthY(int widthY);
    void setCleanliness(int cleanliness);

    void addAnimal(Animal* animal);
    void removeAnimal(string name);

private:
    string habitatType;
    int widthX;
    int widthY;
    int numAnimals;
    vector<Animal*> animals;
    int cleanliness;
};


#endif //OOPZOO_HABITAT_H
