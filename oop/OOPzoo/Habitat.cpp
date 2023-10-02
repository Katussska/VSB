#include "Habitat.h"

string Habitat::getHabitatType() const { return habitatType; }
int Habitat::getWidthX() const { return widthX; }
int Habitat::getWidthY() const { return widthY; }
int Habitat::getNumAnimals() const { return numAnimals; }
vector<Animal *> Habitat::getAnimals() const { return animals; }
void Habitat::setHabitatType(string habitatType) { this->habitatType = habitatType; }
void Habitat::setWidthX(int widthX) { this->widthX = widthX; }
void Habitat::setWidthY(int widthY) { this->widthY = widthY; }

void Habitat::addAnimal(Animal *animal) {
    animals.push_back(animal);
    numAnimals++;
}

void Habitat::removeAnimal(string name) {
    for (int i = 0; i < numAnimals; i++) {
        if (animals[i]->getName() == name) {
            animals.erase(animals.begin() + i);
            numAnimals--;
            break;
        }
    }
}

int Habitat::getCleanliness() const {
    return cleanliness;
}

void Habitat::setCleanliness(int cleanliness) {
    this->cleanliness = cleanliness;
}