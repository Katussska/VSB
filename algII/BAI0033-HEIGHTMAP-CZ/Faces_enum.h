#ifndef FACE_ENUM_H
#define FACE_ENUM_H

#include "Axis_enum.h"

/**
 * @brief Výčtový typ představující různé stěny.
 */
enum Face {
    FRONT, ///< Přední stěna
    BACK, ///< Zadní stěna
    RIGHT, ///< Pravá stěna
    LEFT, ///< Levá stěna
    TOP, ///< Horní stěna
    BOTTOM ///< Spodní stěna
};

/**
 * @brief Získá stěny na základě dané osy.
 * @param axis Osa pro získání stěn.
 * @return Vektor stěn odpovídající dané ose.
 */
std::vector<Face> getFacesAxis(Axis axis);

#endif // FACE_ENUM_H
