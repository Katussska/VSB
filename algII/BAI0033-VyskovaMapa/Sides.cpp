#include "Sides.h"

/**
 * @brief Retrieves the list of all axes.
 *
 * Provides a vector containing all available axes.
 *
 * @return A vector of Axis enumeration values.
 */
vector<Axis> getAxis() {
    return {Axis::X, Axis::XIn, Axis::Y, Axis::YIn, Axis::Z, Axis::ZIn};
}

/**
 * @brief Retrieves the faces associated with a specific axis.
 *
 * Determines the faces related to the provided axis.
 *
 * @param axis The axis for which faces are required.
 * @return A vector of Face enumeration values corresponding to the provided axis.
 */
vector<Face> getFacesAxis(Axis axis) {
    if (axis == Axis::X || axis == Axis::XIn) {
        return {Face::LEFT, Face::RIGHT, Face::TOP, Face::BOTTOM};
    } else if (axis == Axis::Y || axis == Axis::YIn) {
        return {Face::FRONT, Face::BACK, Face::TOP, Face::BOTTOM};
    } else if (axis == Axis::Z || axis == Axis::ZIn) {
        return {Face::FRONT, Face::BACK, Face::LEFT, Face::RIGHT};
    } else {
        return {};
    }
}

/**
 * @brief Retrieves ColumnData based on the specified axis.
 *
 * Provides ColumnData related to the given axis.
 *
 * @param axis The axis for which ColumnData is required.
 * @return ColumnData containing obstruction face and adjacent faces based on the axis.
 */
ColumnData getColumnData(Axis axis) {
    ColumnData data;
    switch (axis) {
        case Axis::X:
            data.obstruction = Face::FRONT;
            break;
        case Axis::XIn:
            data.obstruction = Face::BACK;
            break;
        case Axis::Y:
            data.obstruction = Face::LEFT;
            break;
        case Axis::YIn:
            data.obstruction = Face::RIGHT;
            break;
        case Axis::Z:
            data.obstruction = Face::BOTTOM;
            break;
        case Axis::ZIn:
            data.obstruction = Face::TOP;
            break;
        default:
            break;
    }
    data.adjFaces = getFacesAxis(axis);
    return data;
}