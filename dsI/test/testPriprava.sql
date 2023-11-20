-- Poznámka: Žádné ze zde uvedených řešení si nenárokuje titul "jediné správné řešení".
-- Vždy existuje mnoho variant zápisu a ideálně byste měli být schopni to zapsat i jinak než je uvedeno v řešení.

-- Úterý 12:30

-- A

-- 1. Pro každé volební období nalezněte osobu, která prohlásila nejvíce různých hlasování za zmatečné (informace o tom naleznete v tabulce zmatecne_hlasovani_poslanec).
-- Vypište id_osoba, jméno, příjmení, id_organ daného volebního období a počet různých hlasování, které v období prohlásila osoba za zmatečné.
WITH tab AS (SELECT osoba.id_osoba, osoba.jmeno, osoba.prijmeni, schuze.id_organ, COUNT(DISTINCT zhp.id_hlasovani) cnt
             FROM schuze
                      JOIN hlasovani ON schuze.schuze = hlasovani.schuze AND
                                        schuze.id_organ = hlasovani.id_organ
                      JOIN zmatecne_hlasovani_poslanec zhp ON hlasovani.id_hlasovani = zhp.id_hlasovani
                      JOIN osoba ON osoba.id_osoba = zhp.id_osoba
             GROUP BY osoba.id_osoba, osoba.jmeno, osoba.prijmeni, schuze.id_organ)
SELECT *
FROM tab t1
WHERE cnt >= ALL (SELECT t2.cnt
                  FROM tab t2
                  WHERE t2.id_organ = t1.id_organ)
ORDER BY id_organ

WITH POCTY AS (SELECT o.id_osoba, o.jmeno, o.prijmeni, hl.id_organ, COUNT(CASE WHEN hlp.mode = 1 THEN 1 END) AS pocty
               FROM schuze s
                        JOIN hlasovani hl ON s.id_organ = hl.id_organ AND s.schuze = hl.schuze
                        JOIN zmatecne_hlasovani_poslanec hlp ON hlp.id_hlasovani = hl.id_hlasovani
                        JOIN osoba o ON hlp.id_osoba = o.id_osoba
               GROUP BY o.id_osoba, o.jmeno, o.prijmeni, hl.id_organ)
SELECT *
FROM POCTY p1
WHERE p1.pocty >= ALL (SELECT p2.pocty
                       FROM POCTY p2
                       WHERE p1.id_organ = p2.id_organ)
ORDER BY p1.id_organ

-- 2. Napište dotaz, který pro hlasování konané 24.10.2019 (hlasovani.datum = '2019-10-24') s číslem 172 vypíše následující údaje:
-- 1. id_hlasovani, datum, nazev_dlouhy
-- 2. kolik poslanců ODS hlasovalo PRO,
-- 3. kolik poslanců strany ANO hlasovalo PRO,
-- Hlasování PRO se pozná tak, že v hlasovani_poslanec.vysledek = 'A'.
SELECT id_hlasovani,
       datum,
       nazev_dlouhy,
       (SELECT COUNT()
        FROM poslanec p
                 JOIN zarazeni z ON p.id_osoba = z.id_osoba AND z.cl_funkce = 0
                 JOIN organ org ON z.id_of = org.id_organ
                 JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
                 JOIN hlasovani_poslanec hp ON hp.id_poslanec = p.id_poslanec
        WHERE org.zkratka = 'ANO'
          AND psp2013.nazev_organu_cz = 'Poslanecká sněmovna'
          AND YEAR(psp2013.od_organ) = 2017
          AND hh.id_hlasovani = hp.id_hlasovani
          AND hp.vysledek = 'A') Ano_pro,
       (SELECT COUNT()
        FROM poslanec p
                 JOIN zarazeni z ON p.id_osoba = z.id_osoba AND z.cl_funkce = 0
                 JOIN organ org ON z.id_of = org.id_organ
                 JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
                 JOIN hlasovani_poslanec hp ON hp.id_poslanec = p.id_poslanec
        WHERE org.zkratka = 'ODS'
          AND psp2013.nazev_organu_cz = 'Poslanecká sněmovna'
          AND YEAR(psp2013.od_organ) = 2017
          AND hh.id_hlasovani = hp.id_hlasovani
          AND hp.vysledek = 'A') ODS_pro
FROM hlasovani hh
WHERE hh.datum = '2019-10-24'
  AND cislo = 172

-- varianta s conditional aggregation
SELECT hh.id_hlasovani,
       hh.datum,
       hh.nazev_dlouhy,
       COUNT(CASE WHEN org.zkratka = 'ANO' AND hp.vysledek = 'A' THEN 1 END) Ano_pro,
       COUNT(CASE WHEN org.zkratka = 'ODS' AND hp.vysledek = 'A' THEN 1 END) ODS_pro
FROM poslanec p
         JOIN zarazeni z ON p.id_osoba = z.id_osoba AND z.cl_funkce = 0
         JOIN organ org ON z.id_of = org.id_organ
         JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
         JOIN hlasovani_poslanec hp ON hp.id_poslanec = p.id_poslanec
         JOIN hlasovani hh ON hh.id_hlasovani = hp.id_hlasovani
WHERE psp2013.nazev_organu_cz = 'Poslanecká sněmovna'
  AND YEAR(psp2013.od_organ) = 2017
  AND hh.datum = '2019-10-24'
  AND cislo = 172
GROUP BY hh.id_hlasovani, hh.datum, hh.nazev_dlouhy, hh.pro, hh.proti, hh.prihlaseno

-- 3. Nalezněte schůze (id_schuze, schuze, od_schuze) zasahující do roku 2020, ve kterých se nekonalo ani jedno zmatečné hlasování.
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

-- 2. Napište dotaz, který pro hlasování konané 29.9.2020 (hlasovani.datum = '2020-09-29') s číslem 249 (t.j hlasovani.cislo) vypíše následující údaje:
-- 1. id_hlasovani, datum, nazev_dlouhy
-- 2. kolik poslanců ODS hlasovalo PRO,
-- 3. kolik poslanců strany ANO hlasovalo PRO,
-- Hlasování PRO se pozná tak, že v hlasovani_poslanec.vysledek = 'A'.
SELECT hh.id_hlasovani,
       hh.datum,
       hh.nazev_dlouhy,
       hh.cislo,
       COUNT(CASE WHEN org.zkratka = 'ODS' AND hp.vysledek = 'A' THEN 1 END) SPD_pro,
       COUNT(CASE WHEN org.zkratka = 'ANO' AND hp.vysledek = 'A' THEN 1 END) ODS_pro
FROM poslanec p
         JOIN zarazeni z ON p.id_osoba = z.id_osoba AND z.cl_funkce = 0
         JOIN organ org ON z.id_of = org.id_organ
         JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
         JOIN hlasovani_poslanec hp ON hp.id_poslanec = p.id_poslanec
         JOIN hlasovani hh ON hh.id_hlasovani = hp.id_hlasovani
WHERE psp2013.nazev_organu_cz = 'Poslanecká sněmovna'
  AND YEAR(psp2013.od_organ) = 2017
  AND hh.datum = '2020-09-29'
  AND cislo = 249
GROUP BY hh.id_hlasovani, hh.datum, hh.nazev_dlouhy, hh.cislo


-- Úterý 14:15

-- A

-- 1. Nalezněte poslanecké kluby, které měly dvě a více volebních období v Poslanecké sněmovně minimálně s 50 poslanci
-- (stačí počet záznamů v tabulce poslanec pro dané období).
-- Vypište zkratku poslaneckého klubu a počet volebních období, kdy měl poslanecký klub více než 50 poslanců.
-- Poslanecký klub je záznam v organ pro který typ_organu.nazev_typ_org_cz = 'klub'.
SELECT t.zkratka, COUNT()
FROM (SELECT org.zkratka, org.nazev_organu_cz, psp2013.od_organ, COUNT() cnt
      FROM poslanec p
               JOIN zarazeni z ON p.id_osoba = z.id_osoba AND z.cl_funkce = 0
               JOIN organ org ON z.id_of = org.id_organ
               JOIN typ_organu typo ON org.id_typ_org = typo.id_typ_org
               JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
      WHERE typo.nazev_typ_org_cz = 'klub'
      GROUP BY org.zkratka, psp2013.od_organ, org.nazev_organu_cz
      HAVING COUNT() >= 50) t
GROUP BY t.zkratka
HAVING COUNT() >= 2

-- 2. Pro každou schůzi ve volebním období 2013 - 2017 nalezněte poslední hlasování.
-- K porovnání pořadí můžete využít atribut hlasovani.cislo.
-- Tzn. zajímá nás hlasování s nejvyšší hodnotou atributu hlasovani.cislo v rámci jedné schůze.
-- Seřaďte výsledek podle atributu schuze.schuze a vypište atributy id_hlasovani, schuze, cislo a schuze.nazev_dlouhy.
SELECT s.id_schuze, h.id_hlasovani, s.schuze, h.cislo, h.nazev_dlouhy
FROM schuze s
         JOIN organ ON s.id_organ = organ.id_organ AND YEAR(organ.od_organ) = 2013
         JOIN hlasovani h ON s.schuze = h.schuze AND h.id_organ = s.id_organ
WHERE h.cislo = (SELECT MAX(h2.cislo)
                 FROM hlasovani h2
                          JOIN schuze s2 ON h2.schuze = s2.schuze AND h2.id_organ = s2.id_organ
                 WHERE s2.id_schuze = s.id_schuze
                   AND s2.id_organ = s.id_organ)
ORDER BY s.schuze

/*
   Dotaz A.3:
   Najděte osoby, které nikdy ve volebním období 2017 až 2021 nehlásily PRO ("A") u hlasování,
   jehož dlouhý název začíná "Návrh na vyslovení nedůvěry vládě" (tj. hlasování.nazev_dlouhy).
   Vyberte pouze osoby, které hlasovaly v nějakém takovém hlasování, ale nikdy nehlasovaly pro.
   Vypište všechny údaje o osobě a setřiďte je podle id_osoba.
   Hlasování PRO se pozná tak, že v hlasovani_poslanec.vysledek = 'A'.
*/
SELECT *
FROM osoba
WHERE NOT EXISTS (SELECT 1
                  FROM hlasovani
                           JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                           JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                           JOIN organ ON hlasovani.id_organ = organ.id_organ
                  WHERE nazev_dlouhy LIKE 'Návrh na vyslovení nedůvěry vládě%'
                    AND YEAR(organ.od_organ) BETWEEN 2017 AND 2021
                    AND hp.vysledek = 'A'
                    AND poslanec.id_osoba = osoba.id_osoba)
  AND EXISTS (SELECT 1
              FROM hlasovani
                       JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                       JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                       JOIN organ ON hlasovani.id_organ = organ.id_organ
              WHERE nazev_dlouhy LIKE 'Návrh na vyslovení nedůvěry vládě%'
                AND YEAR(organ.od_organ) BETWEEN 2017 AND 2021
                AND poslanec.id_osoba = osoba.id_osoba)
ORDER BY id_osoba;

/*
   Dotaz B.1:
   Najděte volební období, ve kterých byly v Poslanecké sněmovně alespoň dva kluby s minimálně 50 poslanci
   (počet záznamů v tabulce poslanec pro dané období).
   Vypište identifikátor volebního období (id_organ), kdy toto období začínalo, a počet klubů s více než 50 poslanci.
   Poslanecký klub je záznam v organ pro který typ_organu.nazev_typ_org_cz = 'klub'.
*/
SELECT t.id_organ, t.od_organ, COUNT(*)
FROM (SELECT psp2013.id_organ, org.zkratka, org.nazev_organu_cz, psp2013.od_organ, COUNT(*) cnt
      FROM poslanec p
               JOIN zarazeni z ON p.id_osoba = z.id_osoba AND z.cl_funkce = 0
               JOIN organ org ON z.id_of = org.id_organ
               JOIN typ_organu typo ON org.id_typ_org = typo.id_typ_org
               JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
      WHERE typo.nazev_typ_org_cz = 'klub'
      GROUP BY org.zkratka, psp2013.od_organ, org.nazev_organu_cz, psp2013.id_organ
      HAVING COUNT(*) >= 50) t
GROUP BY t.id_organ, t.od_organ
HAVING COUNT(*) >= 2;

/*
   Dotaz B.2:
   Pro každou schůzi ve volebním období 2002 až 2006 najděte poslední hlasování.
   K porovnání pořadí můžete využít atribut hlasovani.cislo.
   Tzn. zajímá nás hlasování s nejvyšší hodnotou atributu hlasovani.cislo v rámci jedné schůze.
   Setřiďte výsledek podle atributu schuze.schuze a vypište atributy id_hlasovani, schuze, cislo a schuze.nazev_dlouhy.
*/
WITH tab AS (SELECT hlasovani.*
             FROM schuze
                      JOIN hlasovani ON schuze.schuze = hlasovani.schuze
                      JOIN organ ON organ.id_organ = schuze.id_organ
             WHERE YEAR(organ.od_organ) BETWEEN 2002 AND 2006)
SELECT id_hlasovani, schuze, cislo, nazev_dlouhy
FROM tab t1
WHERE t1.cislo >= ALL (SELECT cislo
                       FROM tab t2
                       WHERE t1.schuze = t2.schuze)
ORDER BY t1.schuze;
SELECT hlasovani.*
FROM schuze
         JOIN hlasovani ON schuze.schuze = hlasovani.schuze
    AND schuze.id_organ = hlasovani.id_organ
         JOIN organ ON organ.id_organ = schuze.id_organ
WHERE YEAR(organ.od_organ) = 2002
  AND schuze.schuze = 1;

/*
   Dotaz A.3:
   Najděte osoby, které nikdy ve volebním období 2017 - 2021 nehlasovaly PRO u hlasování,
   jehož dlouhý název (t.j. hlasovani.nazev_dlouhy) obsahuje "COVID".
   Vyberte pouze osoby, které hlasovaly v nějakém takovém hlasování, ale nikdy nehlasovaly PRO.
   Vypište všechny údaje osoby a setřiďte je podle id_osoba.
   Hlasování PRO se pozná tak, že v hlasovani_poslanec.vysledek = 'A'.
*/
SELECT *
FROM osoba
WHERE NOT EXISTS (SELECT 1
                  FROM hlasovani
                           JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                           JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                           JOIN organ ON hlasovani.id_organ = organ.id_organ
                  WHERE nazev_dlouhy LIKE '%COVID%'
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

-- Příklad 1: Vypište osoby, které byly jmenovány do Vlády ČR v období Poslanecké sněmovny, aniž by získaly mandát ve volbách v tomto období poslanecké sněmovny.
-- Pro každou osobu vypište: id_osoba, jméno a příjmení, počet takových jmenování, počet měsíců ve vládě pro taková jmenování.
-- Setřiďte dle počtu takových jmenování. Uvažujte pouze osoby, které byly takto jmenovány nejméně 3x.
SELECT o1.id_osoba,
       o1.jmeno,
       o1.prijmeni,
       COUNT(*)                               AS pocet_jmenovani,
       SUM(DATEDIFF(MONTH, z1.od_o, z1.do_o)) AS pocet_mesicu_ve_vlade
FROM osoba o1
         JOIN zarazeni z1 ON o1.id_osoba = z1.id_osoba
         JOIN organ org1 ON z1.id_of = id_organ AND z1.cl_funkce = 0
WHERE org1.nazev_organu_cz LIKE 'Vláda České republiky'
  AND NOT EXISTS (SELECT 1
                  FROM osoba o2
                           JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
                           JOIN organ org2 ON z2.id_of = org2.id_organ AND z2.cl_funkce = 0
                  WHERE org2.nazev_organu_cz LIKE 'Poslanecká sněmovna'
                    AND (o1.id_osoba = o2.id_osoba AND z1.od_o BETWEEN org2.od_organ AND org2.do_organ))
GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni
HAVING COUNT(*) > 2
ORDER BY pocet_jmenovani DESC;

-- Příklad 2: Vypište osoby, které se častěji omlouvaly v lednu než v únoru a zároveň počet omluv v lednu > 33.
-- Setřiďte sestupně dle počtu omluv v lednu.
SELECT *
FROM (SELECT os.id_osoba,
             os.jmeno,
             os.prijmeni,
             COUNT(CASE WHEN MONTH(om.den) = 1 THEN 1 END) AS pocet_dnu_leden,
             COUNT(CASE WHEN MONTH(om.den) = 2 THEN 1 END) AS pocet_dnu_unor
      FROM osoba os
               JOIN poslanec p ON os.id_osoba = p.id_osoba
               JOIN omluva om ON om.id_poslanec = p.id_poslanec
      GROUP BY os.id_osoba, os.jmeno, os.prijmeni) t
WHERE t.pocet_dnu_leden > 33
  AND t.pocet_dnu_leden > t.pocet_dnu_unor
ORDER BY t.pocet_dnu_leden DESC;

-- Příklad 3: Vypište osoby, které byly místopředsedou sněmovny (typ_funkce.typ_funkce_cz='Místopředseda',
-- typ_organu.nazev_typ_org_cz='Parlament') více než jednou. Pro každou osobu uveďte:
--   id_osoba, jméno, příjmení, počet těchto funkcí, počet členství v delegacích
--   (typ_organu.nazev_typ_org_cz='Delegace').
-- Setřiďte sestupně dle počtu místopřesednické funkce.

SELECT o.id_osoba,
       o.jmeno,
       o.prijmeni,
       COUNT(*)                         AS pocet,
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
ORDER BY pocet DESC;

-- Příklad 1: Vypište osoby, které byly v nějakém výboru poslanecké sněmovny
-- (typ_organ.nazev_typ_org_cz='Výbor') a zároveň ve stejném volebním období
-- (tj. orgány mají stejnou hodnotu organ.rodic_id_organ) nebyly
-- v žádné delegaci poslanecké sněmovny (typ_organ.nazev_typ_org_cz='Delegace').
-- Pro každou osobu vypište:
--   id_osoba, jméno a příjmení osoby, počet takových členství ve výborech,
--   počet všech členství v delegacích (pokud nebyl poslanec členem žádné delegace,
--   vypište hodnotu 0).
-- Setřiďte dle počtu členství ve všech delegacích.
-- Uvažujte pouze osoby, které byly členy takových výborů 8x.

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
ORDER BY pocet_delegace DESC;

/* Výsledek: 25 záznamů
id_osoba jmeno prijmeni pocet_vybor pocet_delegace
5379 Jan Bauer 8 2
252 Lubomír Zaorálek 8 1
261 Zdeňka Horníková 8 1
356 Michal Doktor 8 0
415 Pavel Suchánek 8 0
...
*/
