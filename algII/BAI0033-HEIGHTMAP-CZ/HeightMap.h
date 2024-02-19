#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "Column.h"

/**
 * @brief Reprezentuje výškovou mapu obsahující sloupce.
 *
 * Třída HeightMap spravuje výškovou mapu složenou z sloupců
 * s funkcionalitami pro stanovení sousedních vztahů,
 * počítání ploch podél os a další.
 */
class HeightMap {
private:
    std::vector<std::shared_ptr<Column>> columns; ///< Vektor uchovávající sdílené ukazatele na sloupce.
    int height; ///< Výška výškové mapy.
    int width{}; ///< Šířka výškové mapy.
    int length{}; ///< Délka výškové mapy.

    /**
     * @brief Načte sloupec na zadané pozici ve výškové mapě.
     *
     * @param x X-ová souřadnice sloupce.
     * @param y Y-ová souřadnice sloupce.
     * @param z Z-ová souřadnice sloupce.
     * @return Sdílený ukazatel na sloupec na zadané pozici.
     */
    [[nodiscard]] std::shared_ptr<Column> fetchColumn(int x, int y, int z) const;

    /**
     * @brief Přiřadí sloupec na zadanou pozici ve výškové mapě.
     *
     * @param x X-ová souřadnice sloupce.
     * @param y Y-ová souřadnice sloupce.
     * @param z Z-ová souřadnice sloupce.
     * @param column Sdílený ukazatel na sloupec, který má být přiřazen.
     */
    void assignColumn(int x, int y, int z, std::shared_ptr<Column> column);

    /**
     * @brief Počítá počet ploch podél konkrétní osy.
     *
     * Určuje počet ploch na zadané ose analýzou sousedních sloupců.
     *
     * @param axis Osa, podél které se počítají plochy.
     * @return Počet ploch na zadané ose.
     */
    [[nodiscard]] int countFacesAtAxis(Axis axis) const;

    /**
     * @brief Získá maximální výšku ze vstupního proudu souboru.
     *
     * Čte hodnoty výšek ze souboru a určuje maximální výšku.
     *
     * @param file Reference na vstupní proud souboru.
     * @return Maximální nalezená výška ve souboru.
     */
    static int getMaxHeight(std::ifstream &file);

    /**
     * @brief Vytváří sloupce na základě dat o výšce ze vstupního proudu souboru.
     *
     * Parsuje data o výšce ze souboru a generuje odpovídající sloupce.
     *
     * @param file Reference na vstupní proud souboru.
     */
    void createColumns(std::ifstream &file);

    /**
     * @brief Stanovuje sousední vztahy mezi sloupci.
     *
     * Prochází sloupce a stanovuje sousední vztahy na základě jejich pozic.
     */
    void establishAdjacents();

public:
    /**
     * @brief Konstruuje objekt HeightMap ze souboru.
     *
     * Konstruuje objekt HeightMap parsující data ze souboru.
     *
     * @param fileName Název souboru obsahujících data výškové mapy.
     */
    explicit HeightMap(const std::string &fileName);

    /**
     * @brief Počítá celkový počet ploch ve výškové mapě.
     *
     * Prochází všechny osy, počítá plochy a sčítá celkové počty.
     *
     * @return Celkový počet ploch ve výškové mapě.
     */
    [[nodiscard]] int countFaces() const;

    /**
     * @brief Destruktor třídy HeightMap.
     *
     * Uvolňuje alokovanou paměť a prostředky.
     */
    ~HeightMap();
};

#endif // HEIGHTMAP_H
