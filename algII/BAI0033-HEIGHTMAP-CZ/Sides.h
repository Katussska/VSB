#ifndef STRANY_H
#define STRANY_H

#pragma once

#include <vector>
#include "Faces_enum.h"
#include "Axis_enum.h"

using namespace std;

/**
 * @brief Struktura pro uchování informací o datech sloupce.
 *
 * Obsahuje vektor sousedních stěn a stěnu překážky.
 */
struct ColumnData {
    vector<Face> adjFaces; ///< Vektor sousedních stěn.
    Face obstruction;      ///< Stěna překážky.
};

/**
 * @brief Získává ColumnData na základě zadané osy.
 *
 * Poskytuje ColumnData související s danou osou.
 *
 * @param axis Os, pro kterou je požadován ColumnData.
 * @return ColumnData obsahující stěnu překážky a sousední stěny na základě osy.
 */
ColumnData getColumnData(Axis axis);

#endif // STRANY_H
