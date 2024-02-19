#ifndef AXIS_ENUM_H
#define AXIS_ENUM_H

/**
 * @brief Enumeration representing different axes.
 */
enum Axis {
    X,  ///< X-axis
    Y,  ///< Y-axis
    Z,  ///< Z-axis
    XIn,  ///< Inverted X-axis
    YIn,  ///< Inverted Y-axis
    ZIn   ///< Inverted Z-axis
};

/**
 * @brief Function to retrieve a vector of Axis values.
 * @return std::vector<Axis> containing all axes.
 */
std::vector<Axis> getAxis();

#endif // AXIS_ENUM_H
