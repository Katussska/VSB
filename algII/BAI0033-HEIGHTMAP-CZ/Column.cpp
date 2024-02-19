#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include "Column.h"

using namespace std;

/**
 * @brief Konstruktor pro třídu Column.
 * @param x X-ová souřadnice sloupce.
 * @param y Y-ová souřadnice sloupce.
 * @param z Z-ová souřadnice sloupce.
 */
Column::Column(int x, int y, int z) : x(x), y(y), z(z), adjacents(6) /*sousedi*/, isChecked(false) {}

/**
 * @brief Getter pro X-ovou souřadnici sloupce.
 * @return X-ová souřadnice sloupce.
 */
int Column::getX() const { return x; }

/**
 * @brief Getter pro Y-ovou souřadnici sloupce.
 * @return Y-ová souřadnice sloupce.
 */
int Column::getY() const { return y; }

/**
 * @brief Getter pro Z-ovou souřadnici sloupce.
 * @return Z-ová souřadnice sloupce.
 */
int Column::getZ() const { return z; }

/**
 * @brief Zkontroluje, zda je sloupec označen jako zkontrolován.
 * @return True, pokud je zkontrolován, jinak false.
 */
bool Column::checkIt() const { return isChecked; }

/**
 * @brief Nastaví stav zkontrolování sloupce.
 * @param checked Stav k nastavení (true/false).
 */
void Column::setChecked(bool checked) { isChecked = checked; }

/**
 * @brief Přidá sousední sloupec a stranu ke stávajícímu sloupci.
 * @param column Ukazatel na sousední sloupec.
 * @param face Strana sousedního sloupce.
 */
void Column::addAdjacent(ColumnPtr column, Face face) {
    adjacents[face] = std::move(column);
}

/**
 * @brief Získá sousední sloupce v dané ose.
 * @param axis Osa pro zvážení sousedních sloupců.
 * @return Vektor sousedních sloupců v dané ose.
 */
vector<ColumnPtr> Column::getAdjacentAxis(Axis axis) {
    vector<Face> faces = getFacesAxis(axis);
    vector<ColumnPtr> adjacentColumns;
    std::queue<ColumnPtr> columnQueue;
    columnQueue.push(shared_from_this()); // pushuju column, na ktery volam funkci

    while (!columnQueue.empty()) {
        auto currentColumn = columnQueue.front();
        columnQueue.pop();

        if (currentColumn->isChecked) continue;
        adjacentColumns.push_back(currentColumn);
        currentColumn->isChecked = true;

        for (auto face: faces) {
            auto adjacent = currentColumn->adjacents[face];

            if (adjacent != nullptr && !adjacent->isChecked) {
                columnQueue.push(adjacent);
            }
        }
    }

    return adjacentColumns;
}

/**
 * @brief Kontroluje překážku v dané ose.
 * @param axis Osa pro kontrolu překážky.
 * @return 0, pokud je překážka nalezena, 1, pokud není žádná překážka.
 */
int Column::checkAdj(Axis axis) {
    ColumnData data = getColumnData(axis);
    bool obstructionFound = (adjacents[data.obstruction] != nullptr);
    if (obstructionFound) {
        return 0;
    }

    std::stack<ColumnPtr> columnStack;
    columnStack.push(shared_from_this());

    while (!columnStack.empty()) {
        auto currentColumn = columnStack.top();
        columnStack.pop();

        if (currentColumn->isChecked) continue;
        currentColumn->isChecked = true;

        for (auto face: data.adjFaces) {
            auto adjacent = currentColumn->adjacents[face];
            if (adjacent != nullptr && !adjacent->isChecked && adjacent->adjacents[data.obstruction] == nullptr) {
                columnStack.push(adjacent);
            }
        }
    }

    return 1;
}
