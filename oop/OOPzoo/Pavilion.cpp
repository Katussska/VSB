#include "Pavilion.h"

string Pavilion::getPavilionType() const {
    return pavilionType;
}

vector<Habitat*> Pavilion::getHabitats() const {
    return habitats;
}

void Pavilion::addHabitat(Habitat* habitat) {
    habitats.push_back(habitat);
}

void Pavilion::removeHabitat(string habitatType) {
    for (int i = 0; i < habitats.size(); i++) {
        if (habitats[i]->getHabitatType() == habitatType) {
            habitats.erase(habitats.begin() + i);
            break;
        }
    }
}
