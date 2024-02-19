#include <iostream>
#include "HeightMap.h"

/**
 * @brief Hlavní funkce pro demonstraci funkcí třídy HeightMap.
 *
 * Vytvoří objekt HeightMap ze souboru a zobrazí počet stěn ve výškové mapě.
 *
 * @return 0 při úspěšném provedení.
 */
int main() {
    HeightMap map("../map1.txt"); // Vytvoří objekt HeightMap ze specifikovaného souboru
    std::cout << "Stěny: " << map.countFaces() << std::endl; // Zobrazí počet stěn ve výškové mapě
    return 0;
}
