#include "Sides.h"

/**
 * @brief Získává seznam všech os.
 *
 * Poskytuje vektor obsahující všechny dostupné osy.
 *
 * @return Vektor hodnot osy Axis.
 */
std::vector<Axis> getAxis() {
    return {Axis::X, Axis::XIn, Axis::Y, Axis::YIn, Axis::Z, Axis::ZIn};
}

/**
 * @brief Získává stěny spojené s konkrétní osou.
 *
 * Určuje stěny spojené s poskytnutou osou.
 *
 * @param axis Os, pro kterou jsou potřebné stěny.
 * @return Vektor hodnot osy Face odpovídající zadané ose.
 */
std::vector<Face> getFacesAxis(Axis axis) {
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
 * @brief Získává ColumnData na základě zadané osy.
 *
 * Poskytuje ColumnData související s danou osou.
 *
 * @param axis Os, pro kterou je požadován ColumnData.
 * @return ColumnData obsahující stěnu překážky a sousední stěny na základě osy.
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
