-- 1. Pro každé volební období nalezněte osobu, která prohlásila nejvíce různých hlasování za zmatečné
-- (informace o tom naleznete v tabulce zmatecne_hlasovani_poslanec).
-- Vypište id_osoba, jméno, příjmení, id_organ daného volebního období
-- a počet různých hlasování, které v období prohlásila osoba za zmatečné.

WITH t AS (SELECT osoba.id_osoba,
                  osoba.jmeno,
                  osoba.prijmeni,
                  organ.id_organ                         AS volebni_obdobi,
                  COUNT(DISTINCT hlasovani.id_hlasovani) AS pocet_zmatecnych
           FROM organ
                    JOIN hlasovani ON organ.id_organ = hlasovani.id_organ
                    JOIN zmatecne_hlasovani_poslanec
                         ON hlasovani.id_hlasovani = zmatecne_hlasovani_poslanec.id_hlasovani
                    JOIN osoba ON zmatecne_hlasovani_poslanec.id_osoba = osoba.id_osoba
           WHERE organ.id_organ BETWEEN 165 AND 173
           GROUP BY osoba.id_osoba, osoba.jmeno, osoba.prijmeni, organ.id_organ)
SELECT *
FROM t t1
WHERE pocet_zmatecnych = (SELECT MAX(pocet_zmatecnych)
                          FROM t t2
                          WHERE t1.volebni_obdobi = t2.volebni_obdobi)
ORDER BY volebni_obdobi

-- 2. Napište dotaz, který pro hlasování konané 24.10.2019 (hlasovani.datum = '2019-10-24')
-- s číslem 172 vypíše následující údaje:
-- 2.1 id_hlasovani, datum, nazev_dlouhy
-- 2.2 kolik poslanců ODS hlasovalo PRO,
-- 2.3 kolik poslanců strany ANO hlasovalo PRO,
-- Hlasování PRO se pozná tak, že v hlasovani_poslanec.vysledek = 'A'.

SELECT id_hlasovani,
       datum,
       nazev_dlouhy,
       (SELECT COUNT(*)
        FROM hlasovani_poslanec hp
                 JOIN poslanec p ON hp.id_poslanec = p.id_poslanec
                 JOIN osoba o ON p.id_osoba = o.id_osoba
                 JOIN zarazeni z ON o.id_osoba = z.id_osoba
                 JOIN organ ON z.id_of = organ.id_organ
        WHERE hp.id_hlasovani = hlasovani.id_hlasovani
          AND hp.vysledek = 'A'
          AND organ.zkratka = 'ODS'
          AND organ.rodic_id_organ = hlasovani.id_organ) AS pocet_ods,
       (SELECT COUNT(*)
        FROM hlasovani_poslanec hp
                 JOIN poslanec p ON hp.id_poslanec = p.id_poslanec
                 JOIN osoba o ON p.id_osoba = o.id_osoba
                 JOIN zarazeni z ON o.id_osoba = z.id_osoba
                 JOIN organ ON z.id_of = organ.id_organ
        WHERE hp.id_hlasovani = hlasovani.id_hlasovani
          AND hp.vysledek = 'A'
          AND organ.zkratka = 'ANO'
          AND organ.rodic_id_organ = hlasovani.id_organ) AS pocet_ano
FROM hlasovani
WHERE datum = '2019-10-24'
  AND cislo = 172;

-- 3. Nalezněte schůze (id_schuze, schuze, od_schuze) zasahující do roku 2020,
-- ve kterých se nekonalo ani jedno zmatečné hlasování.
-- Vynechte schůze, ve kterých neproběhlo ani jedno hlasování.
-- Seznam zmatečných hlasování naleznete v tabulce zmatecne.
-- Seřaďte podle id_schuze.

SELECT id_schuze, schuze, od_schuze
FROM schuze s
WHERE NOT EXISTS (SELECT 1
                  FROM hlasovani hh
                           JOIN zmatecne z ON z.id_hlasovani = hh.id_hlasovani
                  WHERE s.schuze = hh.schuze
                    AND s.id_organ = hh.id_organ)
  AND EXISTS (SELECT 1
              FROM hlasovani hh
              WHERE s.schuze = hh.schuze
                AND s.id_organ = hh.id_organ)
  AND (YEAR(s.od_schuze) = 2020 OR YEAR(s.do_schuze) = 2020)
ORDER BY id_schuze

/*
   Najděte osoby, které nikdy ve volebním období 2017 - 2021 nehlasovaly PRO u hlasování,
   jehož dlouhý název (t.j. hlasovani.nazev_dlouhy) obsahuje "COVID".
   Vyberte pouze osoby, které hlasovaly v nějakém takovém hlasování, ale nikdy nehlasovaly PRO.
   Vypište všechny údaje osoby a setřiďte je podle id_osoba.
   Hlasování PRO se pozná tak, že v hlasovani_poslanec.vysledek = 'A'.
*/

SELECT *
FROM osoba
WHERE NOT EXISTS(SELECT 1
                 FROM hlasovani
                          JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                          JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                          JOIN organ ON hlasovani.id_organ = organ.id_organ
                 WHERE hlasovani.nazev_dlouhy LIKE '%COVID%'
                   AND YEAR(organ.od_organ) BETWEEN 2017 AND 2021
                   AND hp.vysledek = 'A'
                   AND poslanec.id_osoba = osoba.id_osoba)
  AND EXISTS (SELECT 1
              FROM hlasovani
                       JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                       JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                       JOIN organ ON hlasovani.id_organ = organ.id_organ
              WHERE nazev_dlouhy LIKE '%COVID%'
                AND YEAR(organ.od_organ) BETWEEN 2017 AND 2021
                AND poslanec.id_osoba = osoba.id_osoba);

