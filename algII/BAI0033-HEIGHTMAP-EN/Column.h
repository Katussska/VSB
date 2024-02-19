#ifndef COLUMN_H
#define COLUMN_H

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Sides.h"

class Column;

using ColumnPtr = std::shared_ptr<Column>;

/**
 * @brief Class representing a Column.
 */
class Column : public std::enable_shared_from_this<Column> {
private:
    std::vector<ColumnPtr> adjacents; ///< Vector of adjacent columns.
    bool isChecked; ///< Flag indicating if the column is checked.
    int x; ///< X-coordinate of the column.
    int y; ///< Y-coordinate of the column.
    int z; ///< Z-coordinate of the column.

public:
    /**
     * @brief Constructor for Column class.
     * @param x X-coordinate of the column.
     * @param y Y-coordinate of the column.
     * @param z Z-coordinate of the column.
     */
    Column(int x, int y, int z);

    /**
     * @brief Getter for the X-coordinate of the column.
     * @return X-coordinate of the column.
     */
    int getX() const;

    /**
     * @brief Getter for the Y-coordinate of the column.
     * @return Y-coordinate of the column.
     */
    int getY() const;

    /**
     * @brief Getter for the Z-coordinate of the column.
     * @return Z-coordinate of the column.
     */
    int getZ() const;

    /**
     * @brief Checks for obstruction along a specific axis.
     * @param axis The axis to check for obstruction.
     * @return 0 if obstruction found, 1 if no obstruction.
     */
    int checkAdj(Axis axis);

    /**
     * @brief Checks if the column is marked as checked.
     * @return True if checked, false otherwise.
     */
    bool checkIt() const;

    /**
     * @brief Sets the checked status of the column.
     * @param checked Status to set (true/false).
     */
    void setChecked(bool checked);

    /**
     * @brief Retrieves adjacent columns along a specific axis.
     * @param axis The axis to consider for adjacent columns.
     * @return Vector of adjacent columns along the specified axis.
     */
    std::vector<ColumnPtr> getAdjacentAxis(Axis axis);

    /**
     * @brief Adds an adjacent column and face to the current column.
     * @param column Pointer to the adjacent column.
     * @param face Face of the adjacent column.
     */
    void addAdjacent(ColumnPtr column, Face face);
};

#endif // COLUMN_H
