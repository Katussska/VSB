#ifndef FACE_ENUM_H
#define FACE_ENUM_H

#include "Axis_enum.h"

/**
 * @brief Enumeration representing different faces.
 */
enum Face {
    FRONT, ///< Front face
    BACK, ///< Back face
    RIGHT, ///< Right face
    LEFT, ///< Left face
    TOP, ///< Top face
    BOTTOM ///< Bottom face
};

/**
 * @brief Retrieves faces based on a given axis.
 * @param axis The axis to retrieve faces for.
 * @return Vector of faces corresponding to the given axis.
 */
std::vector<Face> getFacesAxis(Axis axis);

#endif // FACE_ENUM_H
