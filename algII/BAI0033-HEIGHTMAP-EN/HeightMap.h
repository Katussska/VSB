#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "Column.h"

/**
 * @brief Represents a height map containing columns.
 *
 * The HeightMap class manages a height map composed of columns
 * with functionalities for establishing adjacency relationships,
 * counting faces along axes, and more.
 */
class HeightMap {
private:
    std::vector<std::shared_ptr<Column>> columns; ///< Vector storing shared pointers to columns.
    int height; ///< Height of the height map.
    int width{}; ///< Width of the height map.
    int length{}; ///< Length of the height map.

    /**
     * @brief Retrieves a column at a specified position in the height map.
     *
     * @param x X-coordinate of the column.
     * @param y Y-coordinate of the column.
     * @param z Z-coordinate of the column.
     * @return Shared pointer to the column at the specified position.
     */
    [[nodiscard]] std::shared_ptr<Column> fetchColumn(int x, int y, int z) const;

    /**
     * @brief Assigns a column to a specified position in the height map.
     *
     * @param x X-coordinate of the column.
     * @param y Y-coordinate of the column.
     * @param z Z-coordinate of the column.
     * @param column Shared pointer to the column to be assigned.
     */
    void assignColumn(int x, int y, int z, std::shared_ptr<Column> column);

    /**
     * @brief Counts the number of faces along a specific axis.
     *
     * Determines the number of faces on the given axis by analyzing adjacent columns.
     *
     * @param axis The axis to count faces along.
     * @return The count of faces on the specified axis.
     */
    [[nodiscard]] int countFacesAtAxis(Axis axis) const;

    /**
     * @brief Retrieves the maximum height from a file stream.
     *
     * Reads the height values from a file and determines the maximum height.
     *
     * @param file Reference to the input file stream.
     * @return The maximum height found in the file.
     */
    static int getMaxHeight(std::ifstream &file);

    /**
     * @brief Creates columns based on height data from a file stream.
     *
     * Parses height data from a file and generates columns accordingly.
     *
     * @param file Reference to the input file stream.
     */
    void createColumns(std::ifstream &file);

    /**
     * @brief Establishes adjacency relationships between columns.
     *
     * Iterates through columns and establishes adjacency relationships based on their positions.
     */
    void establishAdjacents();

public:
    /**
     * @brief Constructs a HeightMap object from a file.
     *
     * Constructs a HeightMap object by parsing data from a file.
     *
     * @param fileName The name of the file containing height map data.
     */
    explicit HeightMap(const std::string &fileName);

    /**
     * @brief Counts the total number of faces in the height map.
     *
     * Iterates through all axes to count faces and sums up the totals.
     *
     * @return The total count of faces in the height map.
     */
    [[nodiscard]] int countFaces() const;

    /**
     * @brief Destructor for HeightMap class.
     *
     * Cleans up allocated memory/resources.
     */
    ~HeightMap();
};

#endif // HEIGHTMAP_H
