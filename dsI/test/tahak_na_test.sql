SELECT *
FROM organ
WHERE id_organ BETWEEN 165 AND 173;

SELECT *
FROM typ_organu;

SELECT *
FROM funkce;

SELECT *
FROM schuze;

SELECT *
FROM poslanec;

SELECT *
FROM osoba
ORDER BY id_osoba DESC;

-- ut 1230 a1
-- osoby ktere prohlasily nejvice ruznych hlasovani za zmatecne

WITH t AS
         (SELECT osoba.id_osoba,
                 osoba.jmeno,
                 osoba.prijmeni,
                 organ.id_organ                         AS vol_obdobi,
                 COUNT(DISTINCT hlasovani.id_hlasovani) AS pocet_zmatecnych
          FROM organ
                   JOIN hlasovani ON organ.id_organ = hlasovani.id_organ
                   JOIN zmatecne_hlasovani_poslanec zhp ON zhp.id_hlasovani = hlasovani.id_hlasovani
                   JOIN osoba ON zhp.id_osoba = osoba.id_osoba
          WHERE organ.id_organ BETWEEN 165 AND 173
          GROUP BY osoba.id_osoba, jmeno, prijmeni, organ.id_organ)
SELECT *
FROM t t1
WHERE pocet_zmatecnych = (SELECT MAX(pocet_zmatecnych)
                          FROM t t2
                          WHERE t1.vol_obdobi = t2.vol_obdobi)
ORDER BY vol_obdobi;


-- ut 1230 a2
-- vypiste hlasovani 172 konane 24-10-2019 + kolik poslancu ODS a ANO hlasovalo pro

SELECT id_hlasovani,
       datum,
       nazev_dlouhy,
       (SELECT COUNT(*)
        FROM hlasovani_poslanec hp
                 JOIN poslanec ON hp.id_poslanec = poslanec.id_poslanec
                 JOIN osoba ON poslanec.id_osoba = osoba.id_osoba
                 JOIN zarazeni ON osoba.id_osoba = zarazeni.id_osoba
                 JOIN organ ON zarazeni.id_of = organ.id_organ
        WHERE hp.id_hlasovani = hlasovani.id_hlasovani
          AND hp.vysledek = 'A'
          AND organ.zkratka = 'ODS'
          AND organ.rodic_id_organ = hlasovani.id_organ) AS pocet_ods,
       (SELECT COUNT(*)
        FROM hlasovani_poslanec hp
                 JOIN poslanec ON hp.id_poslanec = poslanec.id_poslanec
                 JOIN osoba ON poslanec.id_osoba = osoba.id_osoba
                 JOIN zarazeni ON osoba.id_osoba = zarazeni.id_osoba
                 JOIN organ ON zarazeni.id_of = organ.id_organ
        WHERE hp.id_hlasovani = hlasovani.id_hlasovani
          AND hp.vysledek = 'A'
          AND organ.zkratka = 'ANO'
          AND organ.rodic_id_organ = hlasovani.id_organ) AS pocet_ano
FROM hlasovani
WHERE datum = '2019-10-24'
  AND cislo = 172;



-- ut 1230 a3
-- schuze v roce 2015, kde nebylo zmatecne hlasovani

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
  AND (YEAR(s.od_schuze) = 2015 OR YEAR(s.do_schuze) = 2015)
ORDER BY id_schuze


-- ut 1230 b1 stejne jak a1

-- ut 1230 b2
-- vypiste hlasovani 249 konane 29-09-2020 + kolik poslancu ODS a ANO hlasovalo pro
SELECT id_hlasovani,
       datum,
       nazev_dlouhy,
       (SELECT COUNT(*)
        FROM hlasovani_poslanec hp
                 JOIN poslanec ON hp.id_poslanec = poslanec.id_poslanec
                 JOIN osoba ON poslanec.id_osoba = osoba.id_osoba
                 JOIN zarazeni ON osoba.id_osoba = zarazeni.id_osoba
                 JOIN organ ON zarazeni.id_of = organ.id_organ
        WHERE hp.id_hlasovani = hlasovani.id_hlasovani
          AND hp.vysledek = 'A'
          AND organ.zkratka = 'ODS'
          AND organ.rodic_id_organ = hlasovani.id_organ) AS pocet_ods,
       (SELECT COUNT(*)
        FROM hlasovani_poslanec hp
                 JOIN poslanec ON hp.id_poslanec = poslanec.id_poslanec
                 JOIN osoba ON poslanec.id_osoba = osoba.id_osoba
                 JOIN zarazeni ON osoba.id_osoba = zarazeni.id_osoba
                 JOIN organ ON zarazeni.id_of = organ.id_organ
        WHERE hp.id_hlasovani = hlasovani.id_hlasovani
          AND hp.vysledek = 'A'
          AND organ.zkratka = 'ANO'
          AND organ.rodic_id_organ = hlasovani.id_organ) AS pocet_ano
FROM hlasovani
WHERE datum = '2020-09-29'
  AND cislo = 249;


-- ut 1230 b3
-- schuze v roce 2020, kde nebylo zmatecne hlasovani

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


-- ut 1415 a1
-- kluby ktere mely vice nez 50 poslancu vice nez 2 vol. obdobi

SELECT t.zkratka, COUNT(*)
FROM (SELECT org.zkratka, org.nazev_organu_cz, psp2013.od_organ, COUNT(*) cnt
      FROM poslanec p
               JOIN zarazeni z ON p.id_osoba = z.id_osoba --zarazeni poslance
               JOIN organ org ON z.id_of = org.id_organ --zarazeni a organ
               JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
      WHERE psp2013.id_organ BETWEEN 165 AND 173
      GROUP BY org.zkratka, psp2013.od_organ, org.nazev_organu_cz
      HAVING COUNT(*) >= 50) t
GROUP BY t.zkratka
HAVING COUNT(*) >= 2


-- ut 1415 a2
-- posledni hlasovani ke kazde schuzi ve vol. obdobi 2013-2017

WITH tab AS (SELECT hlasovani.*
             FROM schuze
                      JOIN hlasovani ON schuze.schuze = hlasovani.schuze AND
                                        schuze.id_organ = hlasovani.id_organ
                      JOIN organ ON organ.id_organ = schuze.id_organ
             WHERE organ.id_organ = 171)
SELECT id_hlasovani, schuze, cislo, nazev_dlouhy
FROM tab t1
WHERE t1.cislo >= ALL (SELECT cislo
                       FROM tab t2
                       WHERE t1.schuze = t2.schuze)
ORDER BY t1.schuze

-- ut 1415 a3
-- osoby ktere v obdobi 2017-2021 nehlasovaly PRO hlasovani, ktere obsahovalo slovo 'neduvery' a ucastnily se toho hlasovani
SELECT *
FROM osoba
WHERE NOT EXISTS (SELECT 1
                  FROM hlasovani
                           JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                           JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                           JOIN organ ON hlasovani.id_organ = organ.id_organ
                  WHERE nazev_dlouhy LIKE '%nedůvěry%'
                    AND YEAR(organ.od_organ) = 2017
                    AND hp.vysledek = 'A'
                    AND poslanec.id_osoba = osoba.id_osoba)
  AND EXISTS (SELECT 1
              FROM hlasovani
                       JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                       JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                       JOIN organ ON hlasovani.id_organ = organ.id_organ
              WHERE nazev_dlouhy LIKE '%nedůvěry%'
                AND YEAR(organ.od_organ) = 2017
                AND poslanec.id_osoba = osoba.id_osoba)
ORDER BY id_osoba


-- ut 1415 b1
-- vol. obdobi, ktere mely aspon 2 kluby s vice jak 50 poslanci

SELECT t.id_organ, t.od_organ, COUNT(*)
FROM (SELECT psp2013.id_organ, org.zkratka, org.nazev_organu_cz, psp2013.od_organ, COUNT(*) cnt
      FROM poslanec p
               JOIN zarazeni z ON p.id_osoba = z.id_osoba --zarazeni poslance
               JOIN organ org ON z.id_of = org.id_organ --zarazeni a organ
               JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
      WHERE psp2013.id_organ BETWEEN 165 AND 173
      GROUP BY org.zkratka, psp2013.od_organ, org.nazev_organu_cz, psp2013.id_organ
      HAVING COUNT(*) >= 50) t
GROUP BY t.id_organ, t.od_organ
HAVING COUNT(*) >= 2


-- ut 1415 b2
-- posledni hlasovani ke kazde schuzi ve vol. obdobi 2002-2006

WITH tab AS (SELECT hlasovani.*
             FROM schuze
                      JOIN hlasovani ON schuze.schuze = hlasovani.schuze AND
                                        schuze.id_organ = hlasovani.id_organ
                      JOIN organ ON organ.id_organ = schuze.id_organ
             WHERE organ.id_organ = 168)
SELECT id_hlasovani, schuze, cislo, nazev_dlouhy
FROM tab t1
WHERE t1.cislo >= ALL (SELECT cislo
                       FROM tab t2
                       WHERE t1.schuze = t2.schuze)
ORDER BY t1.schuze

-- ut 1415 b3
-- osoby ktere v obdobi 2017-2021 nehlasovaly PRO hlasovani, ktere obsahovalo slovo 'COVID' a ucastnily se toho hlasovani
SELECT *
FROM osoba
WHERE NOT EXISTS (SELECT 1
                  FROM hlasovani
                           JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                           JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                           JOIN organ ON hlasovani.id_organ = organ.id_organ
                  WHERE nazev_dlouhy LIKE '%COVID%'
                    AND organ.id_organ = 172
                    AND hp.vysledek = 'A'
                    AND poslanec.id_osoba = osoba.id_osoba)
  AND EXISTS (SELECT 1
              FROM hlasovani
                       JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                       JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                       JOIN organ ON hlasovani.id_organ = organ.id_organ
              WHERE nazev_dlouhy LIKE '%COVID%'
                AND organ.id_organ = 172
                AND poslanec.id_osoba = osoba.id_osoba)
ORDER BY id_osoba

-- st 900 a1
-- osoby ktere byly ve vlade a nebyly poslanci vice jak dvakrat
SELECT o1.id_osoba,
       o1.jmeno,
       o1.prijmeni,
       COUNT(*)                               AS pocet_jmenovani,
       SUM(DATEDIFF(MONTH, z1.od_o, z1.do_o)) AS pocet_mesicu_ve_vlade
FROM osoba o1
         JOIN zarazeni z1 ON o1.id_osoba = z1.id_osoba
         JOIN organ org1 ON z1.id_of = id_organ AND z1.cl_funkce = 0
WHERE org1.nazev_organu_cz LIKE 'Vláda České republiky'
  AND NOT EXISTS
    (SELECT 1
     FROM osoba o2
              JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
              JOIN organ org2 ON z2.id_of = org2.id_organ AND z2.cl_funkce = 0
     WHERE org2.id_organ BETWEEN 165 AND 173
       AND (o1.id_osoba = o2.id_osoba AND z1.od_o BETWEEN org2.od_organ AND org2.do_organ))
GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni
HAVING COUNT(*) > 2
ORDER BY pocet_jmenovani DESC

-- st 900 a2
-- poslanci kteri se omluvali vice krat v lednu nez unoru a meli v lednu vic jak 33 omluv

SELECT *
FROM (SELECT o1.id_osoba,
             o1.jmeno,
             o1.prijmeni,
             COUNT(CASE WHEN MONTH(om.den) = 1 THEN 1 END) AS pocet_dnu_leden,
             COUNT(CASE WHEN MONTH(om.den) = 2 THEN 1 END) AS pocet_dnu_unor
      FROM osoba o1
               JOIN poslanec p ON o1.id_osoba = p.id_osoba
               JOIN omluva om ON p.id_poslanec = om.id_poslanec
      GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni) t
WHERE t.pocet_dnu_leden > 33
  AND t.pocet_dnu_leden > t.pocet_dnu_unor
ORDER BY t.pocet_dnu_leden DESC

-- st 900 a3
-- osoby ktere byly mistopredsedou PSP vice nez jednou a v kolika byli delegacich
SELECT o.id_osoba,
       o.jmeno,
       o.prijmeni,
       COUNT(*)                         AS pocet
        ,
       (SELECT COUNT(*)
        FROM osoba o2
                 JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
                 JOIN organ org2 ON z2.id_of = org2.id_organ AND z2.cl_funkce = 0
                 JOIN typ_organu tor2 ON org2.id_typ_org = tor2.id_typ_org
        WHERE tor2.nazev_typ_org_cz = 'Delegace'
          AND o2.id_osoba = o.id_osoba) AS pocet_clenstvi_delegace
FROM osoba o
         JOIN zarazeni z ON o.id_osoba = z.id_osoba
         JOIN funkce f ON z.id_of = f.id_funkce AND z.cl_funkce = 1
         JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
         JOIN typ_organu tor ON tor.id_typ_org = tf.id_typ_org
WHERE tf.typ_funkce_cz = 'Místopředseda'
  AND tor.nazev_typ_org_cz = 'Parlament'
GROUP BY o.id_osoba, o.jmeno, o.prijmeni
HAVING COUNT(*) > 1
ORDER BY pocet DESC

--st 900 b1
-- vypsat poslance kteri byli ve vyboru a nebyli v delegaci, pouze ty kteri byli ve vyboru 8krat 
SELECT o1.id_osoba,
       o1.jmeno,
       o1.prijmeni,
       COUNT(*)                                      AS pocet_vybor,
       COALESCE(
               (SELECT COUNT(*)
                FROM osoba o2
                         JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
                         JOIN organ org2 ON z2.id_of = id_organ AND z2.cl_funkce = 0
                         JOIN typ_organu tor2 ON org2.id_typ_org = tor2.id_typ_org
                WHERE tor2.nazev_typ_org_cz = 'Delegace'
                  AND o2.id_osoba = o1.id_osoba), 0) AS pocet_delegace
FROM osoba o1
         JOIN zarazeni z1 ON o1.id_osoba = z1.id_osoba
         JOIN organ org1 ON z1.id_of = id_organ AND z1.cl_funkce = 0
         JOIN typ_organu tor1 ON org1.id_typ_org = tor1.id_typ_org
WHERE tor1.nazev_typ_org_cz = 'Výbor'
  AND NOT EXISTS (SELECT 1
                  FROM osoba o2
                           JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
                           JOIN organ org2 ON z2.id_of = id_organ AND z2.cl_funkce = 0
                           JOIN typ_organu tor2 ON org2.id_typ_org = tor2.id_typ_org
                  WHERE tor2.nazev_typ_org_cz = 'Delegace'
                    AND o2.id_osoba = o1.id_osoba
                    AND org1.rodic_id_organ = org2.rodic_id_organ)
GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni
HAVING COUNT(*) = 8
ORDER BY pocet_delegace DESC

-- st 900 b2
-- poslanci kteri se omluvali vice krat v dubnu nez kvetnu a meli v dubnu vic jak 11 omluv
SELECT *
FROM (SELECT o1.id_osoba,
             o1.jmeno,
             o1.prijmeni,
             COUNT(CASE WHEN MONTH(om.den) = 4 THEN 1 END) AS pocet_dnu_duben,
             COUNT(CASE WHEN MONTH(om.den) = 5 THEN 1 END) AS pocet_dnu_kveten
      FROM osoba o1
               JOIN poslanec p ON o1.id_osoba = p.id_osoba
               JOIN omluva om ON p.id_poslanec = om.id_poslanec
      WHERE p.id_organ = 173
      GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni) t
WHERE t.pocet_dnu_duben > 11
  AND t.pocet_dnu_duben > t.pocet_dnu_kveten
ORDER BY t.pocet_dnu_duben DESC

-- st 900 b3
-- poslanci kteri byli vice jak 3krat v ustavne pravnim vyboru
SELECT o.id_osoba,
       o.jmeno,
       o.prijmeni,
       COUNT(*)                         AS pocet_up_vybor,
       (SELECT COUNT(*)
        FROM osoba o2
                 JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
                 JOIN organ org2 ON z2.id_of = org2.id_organ AND z2.cl_funkce = 0
                 JOIN typ_organu tor2 ON org2.id_typ_org = tor2.id_typ_org
        WHERE tor2.nazev_typ_org_cz = 'Výbor'
          AND o2.id_osoba = o.id_osoba) AS pocet_clenstvi_ve_vyborech
FROM osoba o
         JOIN zarazeni z ON o.id_osoba = z.id_osoba
         JOIN organ org ON z.id_of = org.id_organ AND z.cl_funkce = 0
WHERE org.nazev_organu_cz = 'Ústavně právní výbor'
   OR org.nazev_organu_cz = 'Ústavně-právní výbor'
GROUP BY o.id_osoba, o.jmeno, o.prijmeni
HAVING COUNT(*) > 3
ORDER BY pocet_up_vybor DESC


-- st 1045 a1
-- poslanci kteri byli ve stejnem obdobi v unii svobody a nebyli v ODS
SELECT o1.id_osoba,
       o1.jmeno,
       o1.prijmeni,
       SUM(DATEDIFF(MONTH, z1.od_o, z1.do_o)) AS pocet_mesicu_us,
       (SELECT SUM(DATEDIFF(MONTH, z2.od_o, z2.do_o)) AS pocet_mesicu_ods
        FROM osoba o2
                 JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
                 JOIN organ org2 ON z2.id_of = org2.id_organ AND z2.cl_funkce = 0
        WHERE org2.nazev_organu_cz = 'Poslanecká sněmovna'
          AND o2.id_osoba = o1.id_osoba
        GROUP BY o2.id_osoba)                 AS pocet_mesicu_poslanec
FROM osoba o1
         JOIN zarazeni z1 ON o1.id_osoba = z1.id_osoba
         JOIN organ org1 ON z1.id_of = org1.id_organ AND z1.cl_funkce = 0
WHERE org1.nazev_organu_cz = 'Poslanecký klub Unie svobody'
  AND NOT EXISTS (SELECT o3.id_osoba, o3.jmeno, o3.prijmeni
                  FROM osoba o3
                           JOIN zarazeni z3 ON o3.id_osoba = z3.id_osoba
                           JOIN organ org3 ON z3.id_of = org3.id_organ AND z3.cl_funkce = 0
                  WHERE org3.nazev_organu_cz = 'Poslanecký klub Občanské demokratické strany'
                    AND o3.id_osoba = o1.id_osoba
                    AND org3.rodic_id_organ = org1.rodic_id_organ)
GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni
ORDER BY o1.prijmeni


-- st 1045 a2
-- poslanci ODS kteri se omluvali vice krat v listopadu ne prosinci a meli v listopadu vic jak 16 omluv
SELECT *
FROM (SELECT o1.id_osoba,
             o1.jmeno,
             o1.prijmeni,
             COUNT(CASE WHEN MONTH(om.den) = 11 THEN 1 END) AS pocet_dnu_listopad,
             COUNT(CASE WHEN MONTH(om.den) = 12 THEN 1 END) AS pocet_dnu_prosinec
      FROM osoba o1
               JOIN poslanec p ON o1.id_osoba = p.id_osoba
               JOIN omluva om ON p.id_poslanec = om.id_poslanec
      WHERE o1.id_osoba IN (SELECT z.id_osoba
                            FROM zarazeni z
                                     JOIN organ org ON z.id_of = org.id_organ AND z.cl_funkce = 0
                            WHERE org.zkratka = 'ODS')
      GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni) t
WHERE t.pocet_dnu_listopad > 16
  AND t.pocet_dnu_listopad > t.pocet_dnu_prosinec
ORDER BY t.pocet_dnu_listopad DESC


-- alternativni varianta
WITH TAB AS (SELECT DISTINCT z.id_osoba,
                             jmeno,
                             prijmeni,
                             (SELECT COUNT(o.id_poslanec)
                              FROM poslanec
                                       JOIN omluva o ON poslanec.id_poslanec = o.id_poslanec
                              WHERE osoba.id_osoba = poslanec.id_osoba
                                AND MONTH(o.den) = 11
                              HAVING COUNT(o.id_poslanec) > 16) AS omluvy_listopad,
                             (SELECT COUNT(o.id_poslanec)
                              FROM poslanec
                                       JOIN omluva o ON poslanec.id_poslanec = o.id_poslanec
                              WHERE osoba.id_osoba = poslanec.id_osoba
                                AND MONTH(o.den) = 12)          AS omluvy_prosinec
             FROM osoba
                      JOIN zarazeni z ON osoba.id_osoba = z.id_osoba AND cl_funkce = 0
                      JOIN organ o2 ON z.id_of = o2.id_organ
             WHERE o2.nazev_organu_cz = 'Poslanecký klub Občanské demokratické strany')
SELECT *
FROM TAB T1
WHERE T1.omluvy_listopad > T1.omluvy_prosinec
ORDER BY T1.prijmeni


-- poslanci, kteri byli v SPD za obdobi 2017-21
SELECT o1.id_osoba, o1.jmeno, o1.prijmeni
FROM osoba o1
         JOIN poslanec p ON o1.id_osoba = p.id_osoba
         JOIN organ obd ON p.id_organ = obd.id_organ
WHERE o1.id_osoba IN (SELECT z.id_osoba
                      FROM zarazeni z
                               JOIN organ org ON z.id_of = org.id_organ AND z.cl_funkce = 0
                      WHERE org.zkratka = 'SPD')
  AND obd.id_organ = 172
GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni


-- st 1045 a3
-- osoby, ktere byly vic jak 6krat cleny poslaneckeho klubu
SELECT o.id_osoba,
       o.jmeno,
       o.prijmeni,
       org.nazev_organu_cz,
       COUNT(*)                               AS pocet_klubu,
       (SELECT COUNT(*)
        FROM poslanec
        WHERE poslanec.id_osoba = o.id_osoba) AS pocet_volebnich_obdobi
FROM osoba o
         JOIN zarazeni z ON o.id_osoba = z.id_osoba
         JOIN organ org ON z.id_of = org.id_organ AND z.cl_funkce = 0
         JOIN typ_organu tor ON tor.id_typ_org = org.id_typ_org
WHERE tor.nazev_typ_org_cz = 'Klub'
GROUP BY o.id_osoba, o.jmeno, o.prijmeni, org.nazev_organu_cz
HAVING COUNT(*) > 6
ORDER BY pocet_klubu DESC

-- st 1045 b1
-- osoby ktere byly/jsou v TOP 09 a nebyly v ODS
SELECT o1.id_osoba,
       o1.jmeno,
       o1.prijmeni,
       COALESCE(SUM(DATEDIFF(MONTH, z1.od_o, z1.do_o)), SUM(DATEDIFF(MONTH, z1.od_o, GETDATE()))) AS pocet_mesicu_us
FROM osoba o1
         JOIN zarazeni z1 ON o1.id_osoba = z1.id_osoba
         JOIN organ org1 ON z1.id_of = org1.id_organ AND z1.cl_funkce = 0
WHERE org1.nazev_organu_cz = 'Poslanecký klub TOP 09'
  AND NOT EXISTS (SELECT o3.id_osoba, o3.jmeno, o3.prijmeni
                  FROM osoba o3
                           JOIN zarazeni z3 ON o3.id_osoba = z3.id_osoba
                           JOIN organ org3 ON z3.id_of = org3.id_organ AND z3.cl_funkce = 0
                  WHERE org3.nazev_organu_cz = 'Poslanecký klub Občanské demokratické strany'
                    AND o3.id_osoba = o1.id_osoba
                    AND org3.rodic_id_organ = org1.rodic_id_organ)
GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni
ORDER BY o1.prijmeni

-- st 1045 b2
-- poslanci kteri se omlouvali v casteji v prvni polovine roku 2021 nez druhem, vic jak 47 omluv
SELECT *
FROM (SELECT os.id_osoba,
             os.jmeno,
             os.prijmeni,
             COUNT(CASE WHEN MONTH(om.den) >= 1 AND MONTH(om.den) <= 6 THEN 1 END)  AS pocet_dnu_1_6,
             COUNT(CASE WHEN MONTH(om.den) >= 7 AND MONTH(om.den) <= 12 THEN 1 END) AS pocet_dnu_7_12
      FROM osoba os
               JOIN poslanec p ON os.id_osoba = p.id_osoba
               JOIN omluva om ON om.id_poslanec = p.id_poslanec
      WHERE YEAR(om.den) = 2021
      GROUP BY os.id_osoba, os.jmeno, os.prijmeni
      HAVING COUNT(CASE WHEN MONTH(om.den) >= 1 AND MONTH(om.den) <= 6 THEN 1 END) > 47) t
WHERE t.pocet_dnu_1_6 > 47
  AND t.pocet_dnu_1_6 > t.pocet_dnu_7_12
ORDER BY t.pocet_dnu_1_6 DESC

--st 1045 b3
--poslanci kteri zmenili behem tohoto obdobi poslanecky klub
SELECT o.id_osoba,
       o.jmeno,
       o.prijmeni,
       COUNT(DISTINCT org.nazev_organu_cz) AS pocet_ruznych_klubu,
       SUM(DATEDIFF(MONTH, z.od_o, do_o))     pocet_mesicu_ukoncenych_clenstvi
FROM osoba o
         JOIN zarazeni z ON o.id_osoba = z.id_osoba
         JOIN organ org ON z.id_of = org.id_organ AND z.cl_funkce = 0
         JOIN typ_organu tor ON tor.id_typ_org = org.id_typ_org
         JOIN poslanec p ON p.id_osoba = o.id_osoba
         JOIN organ snemovna ON p.id_organ = snemovna.id_organ
WHERE tor.nazev_typ_org_cz = 'Klub'
  AND YEAR(snemovna.od_organ) = 2021
  AND org.od_organ >= snemovna.od_organ
GROUP BY o.id_osoba, o.jmeno, o.prijmeni
HAVING COUNT(DISTINCT org.nazev_organu_cz) > 1
ORDER BY pocet_ruznych_klubu DESC


-- nejvetsi pocet omluv ke kazdemu obdobi
WITH tab AS (SELECT o1.id_osoba, o1.jmeno, o1.prijmeni, org.od_organ, org.do_organ, COUNT(*) AS pocet_omluv
             FROM osoba o1
                      JOIN poslanec p ON o1.id_osoba = p.id_osoba
                      JOIN omluva om ON p.id_poslanec = om.id_poslanec
                      JOIN organ org ON p.id_organ = org.id_organ
             GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni, org.od_organ,
                      org.do_organ) --tabulka vsechny omluvy vsech poslancu v kazdem obdobi
SELECT jmeno, prijmeni, od_organ, COALESCE(do_organ, GETDATE()) AS do_organ, pocet_omluv
FROM tab t1
WHERE t1.pocet_omluv >= ALL (SELECT pocet_omluv
                             FROM tab t2
                             WHERE t1.od_organ = t2.od_organ) -- vybereme nejvetsi pocet omluv z kazdeho volebniho obdobi


SELECT osoba.prijmeni, poslanec.id_osoba, poslanec.id_poslanec, poslanec.id_kraj
FROM poslanec
         JOIN osoba ON osoba.id_osoba = poslanec.id_osoba
WHERE osoba.prijmeni = 'Feri'


-- po 1600 a1

-- nejvetsi pocet omluv poslancu ODS ke kazdemu vol. obdobi
WITH tab AS (SELECT o1.id_osoba, o1.jmeno, o1.prijmeni, org.od_organ, org.do_organ, COUNT(*) AS pocet_omluv
             FROM osoba o1
                      JOIN poslanec p ON o1.id_osoba = p.id_osoba
                      JOIN omluva om ON p.id_poslanec = om.id_poslanec
                      JOIN organ org ON p.id_organ = org.id_organ
             GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni, org.od_organ,
                      org.do_organ) --tabulka vsechny omluvy vsech poslancu v kazdem obdobi
SELECT id_osoba, jmeno, prijmeni, od_organ, do_organ, pocet_omluv
FROM tab t1
WHERE t1.pocet_omluv >= ALL (SELECT pocet_omluv
                             FROM tab t2
                             WHERE t1.od_organ = t2.od_organ) -- vybereme nejvetsi pocet omluv z kazdeho volebniho obdobi
ORDER BY t1.od_organ

WITH tab AS (SELECT os.id_osoba,
                    os.jmeno,
                    os.prijmeni,
                    volebniobdobi.id_organ,
                    volebniobdobi.od_organ,
                    volebniobdobi.do_organ,
                    COUNT(*) AS pocet_omluvenek
             FROM omluva o1
                      JOIN organ volebniobdobi ON o1.id_organ = volebniobdobi.id_organ
                      JOIN poslanec p ON o1.id_poslanec = p.id_poslanec
                      JOIN osoba os ON os.id_osoba = p.id_osoba
             WHERE os.id_osoba IN (SELECT id_osoba
                                   FROM zarazeni
                                            JOIN organ ON zarazeni.id_of = organ.id_organ AND zarazeni.cl_funkce = 0
                                            JOIN typ_organu ON organ.id_typ_org = typ_organu.id_typ_org
                                   WHERE organ.zkratka = 'ODS'
                                     AND typ_organu.nazev_typ_org_cz = 'klub'
                                     AND organ.rodic_id_organ = volebniobdobi.id_organ)
             GROUP BY os.id_osoba, os.jmeno, os.prijmeni, volebniobdobi.id_organ, volebniobdobi.od_organ,
                      volebniobdobi.do_organ)
SELECT *
FROM tab t1
WHERE pocet_omluvenek >= ALL (SELECT pocet_omluvenek
                              FROM tab t2
                              WHERE t1.id_organ = t2.id_organ)
ORDER BY t1.id_organ


-- po 1600 a2
-- osoby ktere byly osoby za VV a Usvit

WITH osoby_v_klubu AS (SELECT z.id_osoba, org.zkratka
                       FROM zarazeni z
                                JOIN organ org ON z.id_of = org.id_organ AND cl_funkce = 0
                                JOIN typ_organu torg ON org.id_typ_org = torg.id_typ_org
                       WHERE torg.nazev_typ_org_cz = 'klub')
SELECT o.jmeno, o.prijmeni, org.zkratka, org.od_organ, org.do_organ
FROM osoba o
         JOIN zarazeni z ON o.id_osoba = z.id_osoba
         JOIN organ org ON z.id_of = org.id_organ
         JOIN typ_organu ON typ_organu.id_typ_org = org.id_typ_org
WHERE o.id_osoba IN (SELECT id_osoba
                     FROM osoby_v_klubu
                     WHERE osoby_v_klubu.zkratka = 'VV')
  AND o.id_osoba IN (SELECT id_osoba
                     FROM osoby_v_klubu
                     WHERE osoby_v_klubu.zkratka = 'Úsvit')
  AND typ_organu.nazev_typ_org_cz = 'klub'

-- po 1600 a3

SELECT s.id_schuze,
       s.schuze,
       s.od_schuze,
       s.do_schuze,
       (SELECT AVG(CAST(hh.proti AS FLOAT))
        FROM hlasovani hh
        WHERE hh.schuze = s.schuze
          AND hh.id_organ = s.id_organ)           AS prumerny_pocet_proti,
       (SELECT COUNT(DISTINCT hh.id_hlasovani)
        FROM hlasovani hh
                 JOIN zmatecne z ON z.id_hlasovani = hh.id_hlasovani
        WHERE hh.schuze = s.schuze
          AND hh.id_organ = s.id_organ)           AS zmatecne_hlasovani,
       (SELECT COUNT(*)
        FROM bod_schuze
        WHERE id_bod_stav = 1
          AND s.id_schuze = bod_schuze.id_schuze) AS pocet_bodu
FROM schuze s
WHERE s.id_organ IN (SELECT org.id_organ
                     FROM organ org
                     WHERE YEAR(org.od_organ) = 2017)
ORDER BY id_schuze

-- po 1600 b1

-- nejvetsi pocet omluv poslancu KSCM ke kazdemu vol. obdobi
WITH tab AS (SELECT o1.id_osoba, o1.jmeno, o1.prijmeni, org.od_organ, org.do_organ, COUNT(*) AS pocet_omluv
             FROM osoba o1
                      JOIN poslanec p ON o1.id_osoba = p.id_osoba
                      JOIN omluva om ON p.id_poslanec = om.id_poslanec
                      JOIN organ org ON p.id_organ = org.id_organ
             WHERE o1.id_osoba IN
                   (SELECT id_osoba
                    FROM zarazeni
                             JOIN organ ON zarazeni.id_of = organ.id_organ AND zarazeni.cl_funkce = 0
                    WHERE organ.zkratka = 'KSČM') -- v klubu KSCM
             GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni, org.od_organ,
                      org.do_organ) --tabulka vsechny omluvy vsech poslancu v kazdem obdobi
SELECT id_osoba, jmeno, prijmeni, od_organ, do_organ, pocet_omluv
FROM tab t1
WHERE t1.pocet_omluv >= ALL (SELECT pocet_omluv
                             FROM tab t2
                             WHERE t1.od_organ = t2.od_organ) -- vybereme nejvetsi pocet omluv z kazdeho volebniho obdobi
ORDER BY t1.od_organ

-- po 1600 b2
-- poslanci kteri byli v klubu TOP09-S a Stan

WITH osoby_v_klubu AS (SELECT z.id_osoba, org.zkratka
                       FROM zarazeni z
                                JOIN organ org ON z.id_of = org.id_organ AND cl_funkce = 0
                                JOIN typ_organu torg ON org.id_typ_org = torg.id_typ_org
                       WHERE torg.nazev_typ_org_cz = 'klub')
SELECT o.jmeno, o.prijmeni, org.zkratka, org.od_organ, org.do_organ
FROM osoba o
         JOIN zarazeni z ON o.id_osoba = z.id_osoba
         JOIN organ org ON z.id_of = org.id_organ
         JOIN typ_organu ON typ_organu.id_typ_org = org.id_typ_org
WHERE o.id_osoba IN (SELECT id_osoba
                     FROM osoby_v_klubu
                     WHERE osoby_v_klubu.zkratka = 'TOP09-S')
  AND o.id_osoba IN (SELECT id_osoba
                     FROM osoby_v_klubu
                     WHERE osoby_v_klubu.zkratka = 'Stan')
  AND typ_organu.nazev_typ_org_cz = 'klub'

-- po 1600 b3
SELECT s.id_schuze,
       s.schuze,
       s.od_schuze,
       s.do_schuze,
       (SELECT AVG(CAST(hh.pro AS FLOAT))
        FROM hlasovani hh
        WHERE hh.schuze = s.schuze
          AND hh.id_organ = s.id_organ)           AS prumerny_pocet_pro,
       (SELECT COUNT(*)
        FROM hlasovani hh
        WHERE hh.schuze = s.schuze
          AND hh.id_organ = s.id_organ
          AND nehlasoval > (prihlaseno / 4))      AS nehlasovala_ctvrtina,
       (SELECT COUNT(*)
        FROM bod_schuze
        WHERE id_bod_stav = 0
          AND s.id_schuze = bod_schuze.id_schuze) AS pocet_bodu
FROM schuze s
WHERE s.id_organ IN (SELECT org.id_organ
                     FROM organ org
                     WHERE YEAR(org.od_organ) = 2021)
ORDER BY id_schuze

-- po 1745 a1

WITH tab AS (SELECT os.id_osoba,
                    os.jmeno,
                    os.prijmeni,
                    p.id_kandidatka,
                    COUNT(*) AS pocet_hlasovani_ne
             FROM osoba os
                      JOIN poslanec p ON os.id_osoba = p.id_osoba
                      JOIN organ volebniobdobi ON volebniobdobi.id_organ = p.id_organ
                      JOIN hlasovani_poslanec hp ON hp.id_poslanec = p.id_poslanec
             WHERE YEAR(volebniobdobi.od_organ) = 2013
               AND hp.vysledek = 'A'
             GROUP BY os.id_osoba, os.jmeno, os.prijmeni, p.id_kandidatka)
SELECT *
FROM tab t1
WHERE pocet_hlasovani_ne >= ALL (SELECT pocet_hlasovani_ne
                                 FROM tab t2
                                 WHERE t1.id_kandidatka = t2.id_kandidatka)
ORDER BY t1.id_kandidatka

-- po 1745 a2
-- osoby ktere byly predsedou zahranicniho vyboru a nebyly mistopredsedou zv

SELECT osoba.id_osoba, jmeno, prijmeni
FROM osoba
WHERE osoba.id_osoba IN (SELECT z.id_osoba
                         FROM zarazeni z
                                  JOIN funkce f ON f.id_funkce = z.id_of AND z.cl_funkce = 1
                                  JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
                                  JOIN organ org ON f.id_organ = org.id_organ
                         WHERE tf.typ_funkce_cz = N'Předseda'
                           AND nazev_organu_cz = 'Zahraniční výbor')
  AND osoba.id_osoba NOT IN (SELECT z.id_osoba
                             FROM zarazeni z
                                      JOIN funkce f ON f.id_funkce = z.id_of AND z.cl_funkce = 1
                                      JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
                                      JOIN organ org ON f.id_organ = org.id_organ
                             WHERE tf.typ_funkce_cz = N'Místopředseda'
                               AND nazev_organu_cz = 'Zahraniční výbor')


-- po 1745 a3
-- najit poslance kteri v obdobi 2013-2017 nehlasovali proti v mimoradne schuzi
SELECT osoba.id_osoba, jmeno, prijmeni
FROM osoba
         JOIN poslanec ON osoba.id_osoba = poslanec.id_osoba
WHERE poslanec.id_poslanec NOT IN (SELECT hp.id_poslanec
                                   FROM hlasovani_poslanec hp
                                            JOIN hlasovani ON hp.id_hlasovani = hlasovani.id_hlasovani
                                            JOIN schuze ON hlasovani.schuze = schuze.schuze AND
                                                           hlasovani.id_organ = schuze.id_organ
                                            JOIN schuze_stav ON schuze_stav.id_schuze = schuze.id_schuze
                                            JOIN organ ON organ.id_organ = schuze.id_organ
                                   WHERE organ.id_organ = 171
                                     AND schuze_stav.typ = 2
                                     AND hp.vysledek IN ('N', 'B'))
  AND poslanec.id_organ IN (SELECT organ.id_organ
                            FROM organ
                            WHERE organ.id_organ = 171)

-- po 1745 b1

WITH tab AS (SELECT os.id_osoba,
                    os.jmeno,
                    os.prijmeni,
                    p.id_kandidatka,
                    COUNT(*) AS pocet_hlasovani_ne
             FROM osoba os
                      JOIN poslanec p ON os.id_osoba = p.id_osoba
                      JOIN organ volebniobdobi ON volebniobdobi.id_organ = p.id_organ
                      JOIN hlasovani_poslanec hp ON hp.id_poslanec = p.id_poslanec
             WHERE YEAR(volebniobdobi.od_organ) = 2017
               AND hp.vysledek IN ('B', 'N')
             GROUP BY os.id_osoba, os.jmeno, os.prijmeni, p.id_kandidatka)
SELECT *
FROM tab t1
WHERE pocet_hlasovani_ne >= ALL (SELECT pocet_hlasovani_ne
                                 FROM tab t2
                                 WHERE t1.id_kandidatka = t2.id_kandidatka)
ORDER BY t1.id_kandidatka

-- po 1745 b2
-- osoby ktere byly predsedou zemedelskeho vyboru a nebyly mistopredsedou zv

SELECT osoba.id_osoba, jmeno, prijmeni
FROM osoba
WHERE osoba.id_osoba IN (SELECT z.id_osoba
                         FROM zarazeni z
                                  JOIN funkce f ON f.id_funkce = z.id_of AND z.cl_funkce = 1
                                  JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
                                  JOIN organ org ON f.id_organ = org.id_organ
                         WHERE tf.typ_funkce_cz = N'Předseda'
                           AND nazev_organu_cz = 'Zemědělský výbor')
  AND osoba.id_osoba NOT IN (SELECT z.id_osoba
                             FROM zarazeni z
                                      JOIN funkce f ON f.id_funkce = z.id_of AND z.cl_funkce = 1
                                      JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
                                      JOIN organ org ON f.id_organ = org.id_organ
                             WHERE tf.typ_funkce_cz = N'Místopředseda'
                               AND nazev_organu_cz = 'Zemědělský výbor')


-- po 1745 b3
-- najit poslance kteri v obdobi 2006-2010 nehlasovali pro v mimoradne schuzi
SELECT osoba.id_osoba, jmeno, prijmeni
FROM osoba
         JOIN poslanec ON osoba.id_osoba = poslanec.id_osoba
WHERE poslanec.id_poslanec NOT IN (SELECT hp.id_poslanec
                                   FROM hlasovani_poslanec hp
                                            JOIN hlasovani ON hp.id_hlasovani = hlasovani.id_hlasovani
                                            JOIN schuze ON hlasovani.schuze = schuze.schuze AND
                                                           hlasovani.id_organ = schuze.id_organ
                                            JOIN schuze_stav ON schuze_stav.id_schuze = schuze.id_schuze
                                            JOIN organ ON organ.id_organ = schuze.id_organ
                                   WHERE organ.id_organ = 169
                                     AND schuze_stav.typ = 2
                                     AND hp.vysledek = 'A')
  AND poslanec.id_organ IN (SELECT organ.id_organ
                            FROM organ
                            WHERE organ.id_organ = 169)

-- ct 900 a1
-- ve volebnim obdobi 2013-17 najdi osoby pro kazdy klub, ktera hlasovala nejvice krat pro

WITH T AS
         (SELECT organ.zkratka, osoba.id_osoba, osoba.jmeno, osoba.prijmeni, COUNT(hp.id_hlasovani) AS hlasovaniPro
          FROM organ volebni_obdobi
                   JOIN organ ON volebni_obdobi.id_organ = organ.rodic_id_organ
                   JOIN typ_organu ON organ.id_typ_org = typ_organu.id_typ_org
                   JOIN zarazeni ON organ.id_organ = zarazeni.id_of AND zarazeni.cl_funkce = 0
                   JOIN osoba ON zarazeni.id_osoba = osoba.id_osoba
                   JOIN poslanec ON osoba.id_osoba = poslanec.id_osoba AND poslanec.id_organ = volebni_obdobi.id_organ
                   JOIN hlasovani_poslanec hp ON poslanec.id_poslanec = hp.id_poslanec AND hp.vysledek = 'A'
          WHERE YEAR(volebni_obdobi.od_organ) = 2013
            AND volebni_obdobi.id_organ BETWEEN 165 AND 173
            AND typ_organu.nazev_typ_org_cz = 'Klub'
          GROUP BY organ.zkratka, osoba.id_osoba, osoba.jmeno, osoba.prijmeni)
SELECT *
FROM T t1
WHERE hlasovaniPro = (SELECT MAX(hlasovaniPro) FROM T t2 WHERE t1.zkratka = t2.zkratka)
ORDER BY t1.zkratka;

-- ct 900 a2
-- schuze kde poslanec MASEK mel vice zmatecnych hlasovani nez poslanec OKAMURA

WITH T AS (SELECT id_schuze,
                  (SELECT COUNT(*)
                   FROM hlasovani
                   WHERE hlasovani.schuze = schuze.schuze
                     AND hlasovani.id_organ = schuze.id_organ
                     AND hlasovani.id_hlasovani IN (SELECT id_hlasovani
                                                    FROM zmatecne_hlasovani_poslanec
                                                             JOIN osoba ON zmatecne_hlasovani_poslanec.id_osoba = osoba.id_osoba
                                                    WHERE osoba.prijmeni = 'Okamura')) AS pocet_okamura,
                  (SELECT COUNT(*)
                   FROM hlasovani
                   WHERE hlasovani.schuze = schuze.schuze
                     AND hlasovani.id_organ = schuze.id_organ
                     AND hlasovani.id_hlasovani IN (SELECT id_hlasovani
                                                    FROM zmatecne_hlasovani_poslanec
                                                             JOIN osoba ON zmatecne_hlasovani_poslanec.id_osoba = osoba.id_osoba
                                                    WHERE osoba.prijmeni = 'Mašek'))   AS pocet_masek
           FROM schuze)
SELECT *
FROM T
WHERE T.pocet_okamura < T.pocet_masek

-- ct 900 a3
-- poslanci kteri ve vol. obdobi 2013-17 nahlasovali na druhe schuzi PRO 'A'

SELECT id_osoba, jmeno, prijmeni
FROM osoba
WHERE NOT EXISTS (SELECT 1
                  FROM hlasovani
                           JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                           JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                           JOIN organ ON hlasovani.id_organ = organ.id_organ
                  WHERE hlasovani.schuze = 2
                    AND YEAR(organ.od_organ) = 2013
                    AND hp.vysledek = 'A'
                    AND poslanec.id_osoba = osoba.id_osoba)
  AND EXISTS (SELECT 1
              FROM hlasovani
                       JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                       JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                       JOIN organ ON hlasovani.id_organ = organ.id_organ
              WHERE hlasovani.schuze = 2
                AND YEAR(organ.od_organ) = 2013
                AND poslanec.id_osoba = osoba.id_osoba)
ORDER BY id_osoba


-- ct 900 b1
-- ve volebnim obdobi 2010-13 najdi osoby pro kazdy klub, ktera hlasovala nejvice krat proti
WITH T AS
         (SELECT organ.zkratka, osoba.id_osoba, osoba.jmeno, osoba.prijmeni, COUNT(hp.id_hlasovani) AS hlasovaniPro
          FROM organ volebni_obdobi
                   JOIN organ ON volebni_obdobi.id_organ = organ.rodic_id_organ
                   JOIN typ_organu ON organ.id_typ_org = typ_organu.id_typ_org
                   JOIN zarazeni ON organ.id_organ = zarazeni.id_of AND zarazeni.cl_funkce = 0
                   JOIN osoba ON zarazeni.id_osoba = osoba.id_osoba
                   JOIN poslanec ON osoba.id_osoba = poslanec.id_osoba AND poslanec.id_organ = volebni_obdobi.id_organ
                   JOIN hlasovani_poslanec hp ON poslanec.id_poslanec = hp.id_poslanec AND hp.vysledek = 'B'
          WHERE YEAR(volebni_obdobi.od_organ) = 2010
            AND volebni_obdobi.id_organ BETWEEN 165 AND 173
            AND typ_organu.nazev_typ_org_cz = 'Klub'
          GROUP BY organ.zkratka, osoba.id_osoba, osoba.jmeno, osoba.prijmeni)
SELECT *
FROM T t1
WHERE hlasovaniPro = (SELECT MAX(hlasovaniPro) FROM T t2 WHERE t1.zkratka = t2.zkratka)
ORDER BY t1.zkratka;

-- ct 900 b2
-- schuze kde poslanec HAVLICEK mel vice zmatecnych hlasovani nez poslanec BABIS

WITH T AS (SELECT id_schuze,
                  (SELECT COUNT(*)
                   FROM hlasovani
                   WHERE hlasovani.schuze = schuze.schuze
                     AND hlasovani.id_organ = schuze.id_organ
                     AND hlasovani.id_hlasovani IN (SELECT id_hlasovani
                                                    FROM zmatecne_hlasovani_poslanec
                                                             JOIN osoba ON zmatecne_hlasovani_poslanec.id_osoba = osoba.id_osoba
                                                    WHERE osoba.prijmeni = 'Babiš'))    AS pocet_babis,
                  (SELECT COUNT(*)
                   FROM hlasovani
                   WHERE hlasovani.schuze = schuze.schuze
                     AND hlasovani.id_organ = schuze.id_organ
                     AND hlasovani.id_hlasovani IN (SELECT id_hlasovani
                                                    FROM zmatecne_hlasovani_poslanec
                                                             JOIN osoba ON zmatecne_hlasovani_poslanec.id_osoba = osoba.id_osoba
                                                    WHERE osoba.prijmeni = 'Havlíček')) AS pocet_havlicek
           FROM schuze)
SELECT *
FROM T
WHERE T.pocet_babis < T.pocet_havlicek

-- ct 900 a3
-- poslanci kteri ve vol. obdobi 2010-13 nehlasovali na ctvrte schuzi PRO 'A'

SELECT id_osoba, jmeno, prijmeni
FROM osoba
WHERE NOT EXISTS (SELECT 1
                  FROM hlasovani
                           JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                           JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                           JOIN organ ON hlasovani.id_organ = organ.id_organ
                  WHERE hlasovani.schuze = 4
                    AND YEAR(organ.od_organ) = 2010
                    AND hp.vysledek = 'A'
                    AND poslanec.id_osoba = osoba.id_osoba)
  AND EXISTS (SELECT 1
              FROM hlasovani
                       JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                       JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                       JOIN organ ON hlasovani.id_organ = organ.id_organ
              WHERE hlasovani.schuze = 4
                AND YEAR(organ.od_organ) = 2010
                AND poslanec.id_osoba = osoba.id_osoba)
ORDER BY id_osoba

-- ct 1045 a1
-- pro kazdou osoby ktere zacina prijmeni na E nalezt obdobi, kde hlasovala nejvice krat pro

WITH T AS
         (SELECT osoba.id_osoba,
                 osoba.jmeno,
                 osoba.prijmeni,
                 od_organ,
                 do_organ,
                 organ.id_organ,
                 COUNT(hlasovani_poslanec.id_poslanec) AS pocetPRO
          FROM osoba
                   JOIN poslanec ON osoba.id_osoba = poslanec.id_osoba
                   JOIN organ ON poslanec.id_organ = organ.id_organ
                   JOIN hlasovani_poslanec
                        ON poslanec.id_poslanec = hlasovani_poslanec.id_poslanec AND hlasovani_poslanec.vysledek = 'A'
          WHERE osoba.prijmeni LIKE 'E%'
          GROUP BY osoba.id_osoba, osoba.jmeno, osoba.prijmeni, organ.id_organ,
                   od_organ, do_organ)
SELECT *
FROM T t1
WHERE t1.pocetPRO = (SELECT MAX(pocetPRO) FROM T t2 WHERE t1.id_osoba = t2.id_osoba);


-- ct 1045 a2
-- poslanci narozeni po roce 1990, kteri byli ve funkci se slovem predseda

SELECT osoba.id_osoba,
       osoba.jmeno,
       osoba.prijmeni,
       (SELECT COUNT(*)
        FROM zarazeni z
                 JOIN osoba o ON osoba.id_osoba = z.id_osoba AND z.cl_funkce = 1
                 JOIN funkce f ON z.id_of = f.id_funkce
        WHERE f.nazev_funkce_cz LIKE '%předseda%'
          AND z.id_osoba = o.id_osoba) AS pocet_predseda,
       (SELECT COUNT(*)
        FROM zarazeni z
                 JOIN osoba o ON osoba.id_osoba = z.id_osoba AND z.cl_funkce = 0
                 JOIN organ org ON z.id_of = org.id_organ
        WHERE org.nazev_organu_cz LIKE '%klub%'
          AND z.id_osoba = o.id_osoba) AS pocet_klub
FROM osoba
WHERE YEAR(osoba.narozeni) > 1990

-- ct 1045 a3
-- poslanci ano, kteri nebyli ve funkci s nazvem ministr

SELECT osoba.id_osoba, osoba.jmeno, osoba.prijmeni
FROM osoba
WHERE osoba.id_osoba IN (SELECT z.id_osoba
                         FROM zarazeni z
                                  JOIN organ org ON z.id_of = org.id_organ AND z.cl_funkce = 0
                         WHERE org.zkratka = 'ANO')
  AND osoba.id_osoba NOT IN (SELECT z.id_osoba
                             FROM zarazeni z
                                      JOIN funkce f ON z.id_of = f.id_funkce AND z.cl_funkce = 1
                                      JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
                             WHERE tf.typ_funkce_cz NOT LIKE '%ministr%')
ORDER BY osoba.id_osoba

-- ct 1045 b1
-- pro kazdou osoby ktere zacina prijmeni na U nalezt obdobi, kde hlasovala nejvice krat proti

WITH T AS
         (SELECT osoba.id_osoba,
                 osoba.jmeno,
                 osoba.prijmeni,
                 od_organ,
                 do_organ,
                 organ.id_organ,
                 COUNT(hlasovani_poslanec.id_poslanec) AS pocetPRO
          FROM osoba
                   JOIN poslanec ON osoba.id_osoba = poslanec.id_osoba
                   JOIN organ ON poslanec.id_organ = organ.id_organ
                   JOIN hlasovani_poslanec ON poslanec.id_poslanec = hlasovani_poslanec.id_poslanec AND
                                              hlasovani_poslanec.vysledek IN ('B', 'N')
          WHERE osoba.prijmeni LIKE 'U%'
          GROUP BY osoba.id_osoba, osoba.jmeno, osoba.prijmeni, organ.id_organ,
                   od_organ, do_organ)
SELECT *
FROM T t1
WHERE t1.pocetPRO = (SELECT MAX(pocetPRO) FROM T t2 WHERE t1.id_osoba = t2.id_osoba);


-- ct 1045 b2
-- poslanci narozeni mezi lety 88 a 90 a kolikrat byli ve vyboru a klubu

SELECT osoba.id_osoba,
       osoba.jmeno,
       osoba.prijmeni,
       (SELECT COUNT(*)
        FROM zarazeni z
                 JOIN osoba o ON osoba.id_osoba = z.id_osoba AND z.cl_funkce = 1
                 JOIN funkce f ON z.id_of = f.id_funkce
        WHERE f.nazev_funkce_cz LIKE '%výbor%'
          AND z.id_osoba = o.id_osoba) AS pocet_predseda,
       (SELECT COUNT(*)
        FROM zarazeni z
                 JOIN osoba o ON osoba.id_osoba = z.id_osoba AND z.cl_funkce = 0
                 JOIN organ org ON z.id_of = org.id_organ
        WHERE org.nazev_organu_cz LIKE '%klub%'
          AND z.id_osoba = o.id_osoba) AS pocet_klub
FROM osoba
WHERE YEAR(osoba.narozeni) BETWEEN 1988 AND 1990

-- ct 1045 b3
-- poslanci ODS, kteri nebyli vedouci

SELECT osoba.id_osoba, osoba.jmeno, osoba.prijmeni
FROM osoba
WHERE osoba.id_osoba IN (SELECT z.id_osoba
                         FROM zarazeni z
                                  JOIN organ org ON z.id_of = org.id_organ AND z.cl_funkce = 0
                         WHERE org.zkratka = 'ODS')
  AND osoba.id_osoba NOT IN (SELECT z.id_osoba
                             FROM zarazeni z
                                      JOIN funkce f ON z.id_of = f.id_funkce AND z.cl_funkce = 1
                                      JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
                             WHERE tf.typ_funkce_cz NOT LIKE '%vedoucí%')
ORDER BY osoba.id_osoba






