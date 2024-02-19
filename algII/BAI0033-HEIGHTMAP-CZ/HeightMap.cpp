#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include "HeightMap.h"

using namespace std;

/**
 * @brief Zkontroluje, zda hodnota leží v daném rozsahu.
 * @param value Hodnota k ověření.
 * @param lowerBound Dolní mez rozsahu.
 * @param upperBound Horní mez rozsahu.
 * @return True, pokud hodnota leží v rozsahu, jinak false.
 */
inline bool isInRange(int value, int lowerBound, int upperBound) {
    return (value >= lowerBound && value <= upperBound);
}

/**
 * @brief Získá sloupec na konkrétní pozici v mapě výšek.
 * @param x X-ová souřadnice sloupce.
 * @param y Y-ová souřadnice sloupce.
 * @param z Z-ová souřadnice sloupce.
 * @return Sdílený ukazatel na sloupec na dané pozici.
 */
std::shared_ptr<Column> HeightMap::fetchColumn(int x, int y, int z) const {
    const bool withinX = isInRange(x, 1, width);
    const bool withinY = isInRange(y, 1, length);
    const bool withinZ = isInRange(z, 1, height);

    if (withinX && withinY && withinZ) {
        return columns[((x - 1) * length * height) + ((y - 1) * height) + ((z - 1))];
    }

    return nullptr;
}

/**
 * @brief Přiřadí sloupec na danou pozici v mapě výšek.
 * @param x X-ová souřadnice sloupce.
 * @param y Y-ová souřadnice sloupce.
 * @param z Z-ová souřadnice sloupce.
 * @param column Sdílený ukazatel na sloupec k přiřazení.
 */
void HeightMap::assignColumn(int x, int y, int z, std::shared_ptr<Column> column) {
    if (isInRange(x, 1, width) && isInRange(y, 1, length) && isInRange(z, 1, height)) {
        columns[((x - 1) * length * height) + ((y - 1) * height) + ((z - 1))] = std::move(column);
    }
}

/**
 * @brief Získá maximální výšku ze vstupního proudu souboru.
 *
 * Přečte hodnoty výšek ze souboru a určí maximální výšku.
 *
 * @param file Reference na vstupní proud souboru.
 * @return Nejvyšší nalezená výška ve souboru.
 */
int HeightMap::getMaxHeight(std::ifstream &file) {
    int width, length, height;
    file >> length >> width;
    height = std::numeric_limits<int>::min(); // Inicializace na minimální možnou hodnotu int
    int count = 0;

    while (count < width * length) {
        int currentHeight;
        if (!(file >> currentHeight)) {
            break; // Přerušení, pokud nelze načíst další výšku
        }
        if (currentHeight > height) {
            height = currentHeight;
        }
        count++;
    }

    return height;
}

/**
 * @brief Vytvoří sloupce na základě dat o výšce ze vstupního proudu souboru.
 *
 * Parsuje data o výšce ze souboru a vytváří podle nich sloupce.
 *
 * @param file Reference na vstupní proud souboru.
 */
void HeightMap::createColumns(std::ifstream &file) {
    int x = 1, y = 1;
    int count = 0;

    int currentHeight;
    while (file >> currentHeight) {
        for (int z = 1; z <= currentHeight; ++z) {
            auto column = std::make_shared<Column>(x, y, z);
            assignColumn(x, y, z, column);
            count++;
        }

        x++;
        if (x > width) {
            x = 1;
            y++;
        }

        if (y > length) {
            break; // Přerušení, pokud je délka překročena
        }
    }
}


/**
 * @brief Stanovuje sousední vztahy mezi sloupci.
 *
 * Projde sloupce a stanovuje sousední vztahy na základě jejich pozic.
 */
void HeightMap::establishAdjacents() {
    for (auto &column: columns) {
        if (column != nullptr) {
            int x = column->getX();
            int y = column->getY();
            int z = column->getZ();

            auto addAdjacentIfNotNull = [&](int dx, int dy, int dz, Face face) {
                auto adjacent = fetchColumn(x + dx, y + dy, z + dz);
                if (adjacent != nullptr) {
                    column->addAdjacent(adjacent, face);
                }
            };

            // Stanovuje sousední sloupce v různých směrech
            addAdjacentIfNotNull(1, 0, 0, Face::FRONT);
            addAdjacentIfNotNull(-1, 0, 0, Face::BACK);
            addAdjacentIfNotNull(0, -1, 0, Face::LEFT);
            addAdjacentIfNotNull(0, 1, 0, Face::RIGHT);
            addAdjacentIfNotNull(0, 0, 1, Face::TOP);
            addAdjacentIfNotNull(0, 0, -1, Face::BOTTOM);
        }
    }
}

/**
 * @brief Počítá počet stěn v zadané ose.
 *
 * Určuje počet stěn v zadané ose analýzou sousedních sloupců.
 *
 * @param axis Osa, podél které se počítají stěny.
 * @return Počet stěn v zadané ose.
 */
int HeightMap::countFacesAtAxis(Axis axis) const {
    int faces = 0;
    vector<vector<shared_ptr<Column>>> bricks;

    for (auto &column: columns) {
        if (column != nullptr && !column->checkIt()) {
            auto adjColumns = column->getAdjacentAxis(axis);
            bricks.push_back(adjColumns);
        }
    }

    // Resetuje kontrolní stav pro všechny sloupce
    for (auto &column: columns) {
        if (column != nullptr) {
            column->setChecked(false);
        }
    }

    for (auto &adjColumns: bricks) {
        for (auto &adjColumn: adjColumns) {
            if (adjColumn != nullptr && !adjColumn->checkIt()) {
                faces += adjColumn->checkAdj(axis);
            }
        }
    }
    return faces;
}

/**
 * @brief Konstruktor pro třídu HeightMap.
 *
 * Vytváří objekt HeightMap zpracováním dat ze souboru.
 *
 * @param fileName Název souboru obsahující data mapy výšek.
 */
HeightMap::HeightMap(const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Nelze otevřít soubor" << endl;
        return;
    }

    height = getMaxHeight(file);
    file.seekg(0);
    file >> length >> width;
    columns = vector<shared_ptr<Column>>(width * length * height);
    createColumns(file);

    file.close();
    establishAdjacents();
}

/**
 * @brief Počítá celkový počet stěn v mapě výšek.
 *
 * Projde všechny osy a spočítá stěny, poté sečte výsledky.
 *
 * @return Celkový počet stěn v mapě výšek.
 */
int HeightMap::countFaces() const {
    int faces = 0;
    std::vector<Axis> axes = getAxis();
    for (auto &axe: axes) {
        faces += countFacesAtAxis(axe);

        // Resetuje kontrolní stav pro všechny sloupce
        for (auto &column: columns) {
            if (column != nullptr) {
                column->setChecked(false);
            }
        }
    }
    return faces;
}

/**
 * @brief Destruktor pro třídu HeightMap.
 *
 * Uvolní alokovanou paměť/ prostředky.
 */
HeightMap::~HeightMap() {}
