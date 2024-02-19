#include <iostream>
#include "HeightMap.h"

/**
 * @brief Main function to demonstrate HeightMap functionalities.
 *
 * Creates a HeightMap object from a file and displays the count of faces in the height map.
 *
 * @return 0 on successful execution.
 */
int main() {
    HeightMap map("../map4.txt"); // Creates a HeightMap object from the specified file
    cout << "Faces: " << map.countFaces() << endl; // Displays the count of faces in the height map
    return 0;
}