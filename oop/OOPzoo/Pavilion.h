// Composition - kompozice (k Habitat class)
// Class in the role of an object - třída v roli objektu
#ifndef OOPZOO_PAVILION_H
#define OOPZOO_PAVILION_H

#include <iostream>
#include <vector>
#include "Habitat.h"

using namespace std;

class Pavilion {
public:
    Pavilion(string pavilionType = "N") : pavilionType(pavilionType) {}
    ~Pavilion() {}

    string getPavilionType() const;
    vector<Habitat*> getHabitats() const;
    void addHabitat(Habitat* habitat);
    void removeHabitat(string habitatType);

private:
    string pavilionType;
    vector<Habitat*> habitats;
};

#endif //OOPZOO_PAVILION_H
