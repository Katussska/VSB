#ifndef COLUMN_H
#define COLUMN_H

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Sides.h"

class Column;

using ColumnPtr = std::shared_ptr<Column>; //inteligentni pointery, ktere se sami mazou (reference)

/**
 * @brief Třída představující sloupec.
 */
class Column : public std::enable_shared_from_this<Column> {
private:
    std::vector<ColumnPtr> adjacents; ///< Vektor sousedních sloupců.
    bool isChecked; ///< Příznak označující, zda je sloupec zkontrolován.
    int x; ///< X-ová souřadnice sloupce.
    int y; ///< Y-ová souřadnice sloupce.
    int z; ///< Z-ová souřadnice sloupce.

public:
    /**
     * @brief Konstruktor pro třídu Column.
     * @param x X-ová souřadnice sloupce.
     * @param y Y-ová souřadnice sloupce.
     * @param z Z-ová souřadnice sloupce.
     */
    Column(int x, int y, int z);

    /**
     * @brief Getter pro X-ovou souřadnici sloupce.
     * @return X-ová souřadnice sloupce.
     */
    int getX() const;

    /**
     * @brief Getter pro Y-ovou souřadnici sloupce.
     * @return Y-ová souřadnice sloupce.
     */
    int getY() const;

    /**
     * @brief Getter pro Z-ovou souřadnici sloupce.
     * @return Z-ová souřadnice sloupce.
     */
    int getZ() const;

    /**
     * @brief Kontroluje překážku v dané ose.
     * @param axis Osa pro kontrolu překážky.
     * @return 0, pokud je překážka nalezena, 1, pokud není žádná překážka.
     */
    int checkAdj(Axis axis);

    /**
     * @brief Zkontroluje, zda je sloupec označen jako zkontrolován.
     * @return True, pokud je zkontrolován, jinak false.
     */
    bool checkIt() const;

    /**
     * @brief Nastaví stav zkontrolování sloupce.
     * @param checked Stav k nastavení (true/false).
     */
    void setChecked(bool checked);

    /**
     * @brief Získá sousední sloupce v dané ose.
     * @param axis Osa pro zvážení sousedních sloupců.
     * @return Vektor sousedních sloupců v dané ose.
     */
    std::vector<ColumnPtr> getAdjacentAxis(Axis axis);

    /**
     * @brief Přidá sousední sloupec a stranu ke stávajícímu sloupci.
     * @param column Ukazatel na sousední sloupec.
     * @param face Strana sousedního sloupce.
     */
    void addAdjacent(ColumnPtr column, Face face);
};

#endif // COLUMN_H
