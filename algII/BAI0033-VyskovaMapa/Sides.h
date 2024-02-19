#ifndef SIDES_H
#define SIDES_H

#pragma once

#include <vector>
#include "Faces_enum.h"
#include "Axis_enum.h"

using namespace std;

/**
 * @brief Structure to hold information about column data.
 *
 * Contains a vector of adjacent faces and an obstruction face.
 */
struct ColumnData {
    vector<Face> adjFaces; ///< Vector of adjacent faces.
    Face obstruction;      ///< Obstruction face.
};

/**
 * @brief Retrieves ColumnData based on the specified axis.
 *
 * Provides ColumnData related to the given axis.
 *
 * @param axis The axis for which ColumnData is required.
 * @return ColumnData containing obstruction face and adjacent faces based on the axis.
 */
ColumnData getColumnData(Axis axis);

#endif // SIDES_H
