#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include "Column.h"

using namespace std;

/**
 * @brief Constructor for Column class.
 * @param x X-coordinate of the column.
 * @param y Y-coordinate of the column.
 * @param z Z-coordinate of the column.
 */
Column::Column(int x, int y, int z) : x(x), y(y), z(z), adjacents(6), isChecked(false) {}

/**
 * @brief Getter for the X-coordinate of the column.
 * @return X-coordinate of the column.
 */
int Column::getX() const { return x; }

/**
 * @brief Getter for the Y-coordinate of the column.
 * @return Y-coordinate of the column.
 */
int Column::getY() const { return y; }

/**
 * @brief Getter for the Z-coordinate of the column.
 * @return Z-coordinate of the column.
 */
int Column::getZ() const { return z; }

/**
 * @brief Checks if the column is marked as checked.
 * @return True if checked, false otherwise.
 */
bool Column::checkIt() const { return isChecked; }

/**
 * @brief Sets the checked status of the column.
 * @param checked Status to set (true/false).
 */
void Column::setChecked(bool checked) { isChecked = checked; }

/**
 * @brief Adds an adjacent column and face to the current column.
 * @param column Pointer to the adjacent column.
 * @param face Face of the adjacent column.
 */
void Column::addAdjacent(ColumnPtr column, Face face) {
    adjacents[face] = std::move(column);
}

/**
 * @brief Retrieves adjacent columns along a specific axis.
 * @param axis The axis to consider for adjacent columns.
 * @return Vector of adjacent columns along the specified axis.
 */
vector<ColumnPtr> Column::getAdjacentAxis(Axis axis) {
    vector<Face> faces = getFacesAxis(axis);
    vector<ColumnPtr> adjacentColumns;
    std::queue<ColumnPtr> columnQueue;
    columnQueue.push(shared_from_this());

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
 * @brief Checks for obstruction along a specific axis.
 * @param axis The axis to check for obstruction.
 * @return 0 if obstruction found, 1 if no obstruction.
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

    return obstructionFound ? 0 : 1;
}