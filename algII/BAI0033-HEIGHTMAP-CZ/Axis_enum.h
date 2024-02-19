#ifndef AXIS_ENUM_H
#define AXIS_ENUM_H

/**
 * @brief Výčet reprezentující různé osy.
 */
enum Axis {
    X,  ///< X-osa
    Y,  ///< Y-osa
    Z,  ///< Z-osa
    XIn,  ///< Opačná X-osa
    YIn,  ///< Opačná Y-osa
    ZIn   ///< Opačná Z-osa
};

/**
 * @brief Funkce pro získání vektoru hodnot os.
 * @return std::vector<Axis> obsahující všechny osy.
 */
std::vector<Axis> getAxis();

#endif // AXIS_ENUM_H
