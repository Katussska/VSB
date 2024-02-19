#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include "HeightMap.h"

using namespace std;

/**
 * @brief Checks if a value is within a specified range.
 * @param value The value to check.
 * @param lowerBound The lower bound of the range.
 * @param upperBound The upper bound of the range.
 * @return True if the value is within the range, false otherwise.
 */
inline bool isInRange(int value, int lowerBound, int upperBound) {
    return (value >= lowerBound && value <= upperBound);
}

/**
 * @brief Retrieves a column at a specific position in the height map.
 * @param x X-coordinate of the column.
 * @param y Y-coordinate of the column.
 * @param z Z-coordinate of the column.
 * @return Shared pointer to the column at the specified position.
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
 * @brief Assigns a column to a specified position in the height map.
 * @param x X-coordinate of the column.
 * @param y Y-coordinate of the column.
 * @param z Z-coordinate of the column.
 * @param column Shared pointer to the column to be assigned.
 */
void HeightMap::assignColumn(int x, int y, int z, std::shared_ptr<Column> column) {
    if (isInRange(x, 1, width) && isInRange(y, 1, length) && isInRange(z, 1, height)) {
        columns[((x - 1) * length * height) + ((y - 1) * height) + ((z - 1))] = std::move(column);
    }
}

/**
 * @brief Retrieves the maximum height from a file stream.
 *
 * Reads the height values from a file and determines the maximum height.
 *
 * @param file Reference to the input file stream.
 * @return The maximum height found in the file.
 */
int HeightMap::getMaxHeight(std::ifstream &file) {
    int width, length, height;
    file >> length >> width;
    height = std::numeric_limits<int>::min(); // Initialize to minimum possible int value
    int count = 0;

    while (count < width * length) {
        int currentHeight;
        if (!(file >> currentHeight)) {
            break; // Break if unable to read the next height
        }
        if (currentHeight > height) {
            height = currentHeight;
        }
        count++;
    }

    return height;
}

/**
 * @brief Creates columns based on height data from a file stream.
 *
 * Parses height data from a file and generates columns accordingly.
 *
 * @param file Reference to the input file stream.
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
            break; // Break if length is exceeded
        }
    }
}


/**
 * @brief Establishes adjacency relationships between columns.
 *
 * Iterates through columns and establishes adjacency relationships based on their positions.
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

            // Establish adjacent columns in various directions
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
 * @brief Counts the number of faces along a specific axis.
 *
 * Determines the number of faces on the given axis by analyzing adjacent columns.
 *
 * @param axis The axis to count faces along.
 * @return The count of faces on the specified axis.
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

    // Reset the checked status for all columns
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
 * @brief Constructor for HeightMap class.
 *
 * Constructs a HeightMap object by parsing data from a file.
 *
 * @param fileName The name of the file containing height map data.
 */
HeightMap::HeightMap(const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Could not open the file" << endl;
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
 * @brief Counts the total number of faces in the height map.
 *
 * Iterates through all axes to count faces and sums up the totals.
 *
 * @return The total count of faces in the height map.
 */
int HeightMap::countFaces() const {
    int faces = 0;
    std::vector<Axis> axes = getAxis();
    for (auto &axe: axes) {
        faces += countFacesAtAxis(axe);

        // Reset the checked status for all columns
        for (auto &column: columns) {
            if (column != nullptr) {
                column->setChecked(false);
            }
        }
    }
    return faces;
}

/**
 * @brief Destructor for HeightMap class.
 *
 * Cleans up allocated memory/resources.
 */
HeightMap::~HeightMap() {}
