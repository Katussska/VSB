-- PoznĂˇmka: ĹľĂˇdnĂ© ze zde uvedenĂ˝ch Ĺ™eĹˇenĂ­ si nenĂˇrokuje titul "jedinnĂ© sprĂˇvnĂ© Ĺ™eĹˇenĂ­".
-- VĹľdy existuje mnoho variant zĂˇpisu a ideĂˇlnÄ› by jste mÄ›li bĂ˝t schopni to zapsat i jinak nÄ›Ĺľ je uvedeno v Ĺ™eĹˇenĂ­

----------------------------------------------------
----------------------------------------------------
-- Ăštery 12:30

-- A

-------
-- 1. Pro kaĹľdĂ© volebnĂ­ obdobĂ­ naleznÄ›te osobu, kterĂˇ prowlĂˇsila nejvĂ­ce rĹŻznĂ˝ch hlasovĂˇnĂ­ za zmateÄŤnĂ© (informace o tom naleznete v tabulce zmatecne_hlasovani_poslanec).
-- VypiĹˇte id_osoba, jmĂ©no, pĹ™Ă­jmenĂ­, id_organ danĂ©ho volebnĂ­ho obdobĂ­ a poÄŤet rĹŻznĂ˝ch hlasovĂˇnĂ­, kterĂ© v obdobĂ­ prohlĂˇsila osoba za zmateÄŤnĂ©.
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

-------------
-- 2. NapiĹˇte dotaz, kterĂ˝ pro hlasovĂˇnĂ­ konanĂ© 24.10.2019 (hlasovani.datum = '2019-10-24') s ÄŤĂ­slem 172 vypĂ­Ĺˇe nĂˇsledujĂ­cĂ­ Ăşdaje: 
-- 1. id_hlasovani, datum, nazev_dlouhy
-- 2. kolik poslancĹŻ ODS hlasovalo PRO,
-- 3. kolik poslancĹŻ strany ANO hlasovalo PRO,
-- HlasovĂˇnĂ­ PRO se poznĂˇ tak, Ĺľe v hlasovani_poslanec.vysledek = 'A'.
SELECT id_hlasovani,
       datum,
       nazev_dlouhy,
       (SELECT COUNT(*)
        FROM poslanec p
                 JOIN zarazeni z ON p.id_osoba = z.id_osoba AND z.cl_funkce = 0
                 JOIN organ org ON z.id_of = org.id_organ
                 JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
                 JOIN hlasovani_poslanec hp ON hp.id_poslanec = p.id_poslanec
        WHERE org.zkratka = 'ANO'
          AND psp2013.nazev_organu_cz = 'PoslaneckĂˇ snÄ›movna'
          AND YEAR(psp2013.od_organ) = 2017
          AND hh.id_hlasovani = hp.id_hlasovani
          AND hp.vysledek = 'A') Ano_pro,
       (SELECT COUNT(*)
        FROM poslanec p
                 JOIN zarazeni z ON p.id_osoba = z.id_osoba AND z.cl_funkce = 0
                 JOIN organ org ON z.id_of = org.id_organ
                 JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
                 JOIN hlasovani_poslanec hp ON hp.id_poslanec = p.id_poslanec
        WHERE org.zkratka = 'ODS'
          AND psp2013.nazev_organu_cz = 'PoslaneckĂˇ snÄ›movna'
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
WHERE psp2013.nazev_organu_cz = 'PoslaneckĂˇ snÄ›movna'
  AND YEAR(psp2013.od_organ) = 2017
  AND hh.datum = '2019-10-24'
  AND cislo = 172
GROUP BY hh.id_hlasovani, hh.datum, hh.nazev_dlouhy, hh.pro, hh.proti, hh.prihlaseno


----------
-- 3. NaleznÄ›te schĹŻze (id_schuze, schuze, od_schuze) zasahujĂ­cĂ­ do roku 2015, ve kterĂ˝ch se nekonalo ani jedno zmateÄŤnĂ© hlasovĂˇnĂ­.
-- Vynechte schĹŻze, ve kterĂ˝ch neprobÄ›hlo ani jedno hlasovĂˇnĂ­.
-- Seznam zmateÄŤnĂ˝ch hlasovĂˇnĂ­ naleznete v tabulce zmatecne.
-- SetĹ™iÄŹte podle id_schuze.
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


-- B

-------
-- 1. Pro kaĹľdĂ© volebnĂ­ obdobĂ­ naleznÄ›te osobu, kterĂˇ prohlĂˇsila nejvĂ­ce rĹŻznĂ˝ch hlasovĂˇnĂ­ za zmateÄŤnĂ© (informace o tom naleznete v tabulce zmatecne_hlasovani_poslanec).
-- VypiĹˇte id_osoba, jmĂ©no, pĹ™Ă­jmenĂ­, id_organ danĂ©ho volebnĂ­ho obdobĂ­ a poÄŤet rĹŻznĂ˝ch hlasovĂˇnĂ­, kterĂ© v obdobĂ­ prohlĂˇsila osoba za zmateÄŤnĂ©.
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


-------------
-- 2. NapiĹˇte dotaz, kterĂ˝ pro hlasovĂˇnĂ­ konanĂ© 29.9.2020 (hlasovani.datum = '2020-09-29') s ÄŤĂ­slem 249 (t.j hlasovani.cislo) vypĂ­Ĺˇe nĂˇsledujĂ­cĂ­ Ăşdaje: 
-- 1. id_hlasovani, datum, nazev_dlouhy
-- 2. kolik poslancĹŻ ODS hlasovalo PRO,
-- 3. kolik poslancĹŻ strany ANO hlasovalo PRO,
-- HlasovĂˇnĂ­ PRO se poznĂˇ tak, Ĺľe v hlasovani_poslanec.vysledek = 'A'.
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
WHERE psp2013.nazev_organu_cz = 'PoslaneckĂˇ snÄ›movna'
  AND YEAR(psp2013.od_organ) = 2017
  AND hh.datum = '2020-09-29'
  AND cislo = 249
GROUP BY hh.id_hlasovani, hh.datum, hh.nazev_dlouhy, hh.cislo


----------
-- 3. NaleznÄ›te schĹŻze (id_schuze, schuze, od_schuze) zasahujĂ­cĂ­ do roku 2020, ve kterĂ˝ch se nekonalo ani jedno zmateÄŤnĂ© hlasovĂˇnĂ­.
-- Vynechte schĹŻze, ve kterĂ˝ch neprobÄ›hlo ani jedno hlasovĂˇnĂ­.
-- Seznam zmateÄŤnĂ˝ch hlasovĂˇnĂ­ naleznete v tabulce zmatecne.
-- SetĹ™iÄŹte podle id_schuze.
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


----------------------------------------------------
----------------------------------------------------
-- ĂšterĂ˝ 14:15

-- A

-------------
-- 1. NaleznÄ›te poslaneckĂ© kluby, kterĂ© mÄ›ly dvÄ› a vĂ­ce volebnĂ­ch obdobĂ­ v poslaneckĂ© snÄ›movnÄ› minimĂˇlnÄ› 50 poslancĹŻ 
-- (staÄŤĂ­ poÄŤet zĂˇznamĹŻ v tabulce poslanec pro danĂ© obdobĂ­).
-- VypiĹˇte zkratku poslaneckĂ©ho klubu a poÄŤet volebnĂ­ch obdobĂ­, kdy mÄ›l poslaneckĂ˝ klub vĂ­ce neĹľ 50 poslancĹŻ.
-- PoslaneckĂ˝ klub je zĂˇznam v organ pro kterĂ˝ typ_organu.nazev_typ_org_cz = 'klub'.
SELECT t.zkratka, COUNT(*)
FROM (SELECT org.zkratka, org.nazev_organu_cz, psp2013.od_organ, COUNT(*) cnt
      FROM poslanec p
               JOIN zarazeni z ON p.id_osoba = z.id_osoba AND z.cl_funkce = 0
               JOIN organ org ON z.id_of = org.id_organ
               JOIN typ_organu typo ON org.id_typ_org = typo.id_typ_org
               JOIN organ psp2013 ON psp2013.id_organ = p.id_organ AND org.rodic_id_organ = psp2013.id_organ
      WHERE typo.nazev_typ_org_cz = 'klub'
      GROUP BY org.zkratka, psp2013.od_organ, org.nazev_organu_cz
      HAVING COUNT(*) >= 50) t
GROUP BY t.zkratka
HAVING COUNT(*) >= 2


------
-- 2. Pro kaĹľdou schĹŻzi ve volebnĂ­m obdobĂ­ 2013 - 2017 naleznÄ›te poslednĂ­ hlasovĂˇnĂ­.
-- K porovnĂˇnĂ­ poĹ™adĂ­ mĹŻĹľete vyuĹľĂ­t atribut hlasovani.cislo. 
-- Tzn. zajĂ­mĂˇ nĂˇs hlasovĂˇnĂ­ s nejvyĹˇĹˇĂ­ hodnotou atributu hlasovani.cislo v rĂˇmci jednĂ© schĹŻze.
-- SetĹ™iÄŹte vĂ˝sledek podle atributu schuze.schuze a vypiĹˇte atributy id_hlasovani, schuze, cislo a schuze.nazev_dlouhy.
WITH tab AS (SELECT hlasovani.*
             FROM schuze
                      JOIN hlasovani ON schuze.schuze = hlasovani.schuze AND
                                        schuze.id_organ = hlasovani.id_organ
                      JOIN organ ON organ.id_organ = schuze.id_organ
             WHERE YEAR(organ.od_organ) = 2013)
SELECT id_hlasovani, schuze, cislo, nazev_dlouhy
FROM tab t1
WHERE t1.cislo >= ALL (SELECT cislo
                       FROM tab t2
                       WHERE t1.schuze = t2.schuze)
ORDER BY t1.schuze

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


------
-- 3. NaleznÄ›te osoby, kterĂ© nikdy ve volebnĂ­m obdobĂ­ 2017 - 2021 nehlasovaly PRO 
-- (hlasovani_poslanec.vysledek = 'A') u hlasovĂˇnĂ­,
-- jehoĹľ dlouhĂ˝ nĂˇzev Ĺ™etÄ›zce zaÄŤĂ­nĂˇ "NĂˇvrh na vyslovenĂ­ nedĹŻvÄ›ry vlĂˇdÄ›" (t.j. hlasovani.nazev_dlouhy).
-- Vyberte pouze osoby, kterĂ© hlasovaly v nÄ›jakĂ© takovĂ©m hlasovĂˇnĂ­, ale nikdy nehlasovali pro.
-- VypiĹˇte vĹˇechny Ăşdaje osoby a setĹ™iÄŹte je podle id_osoba.
-- HlasovĂˇnĂ­ PRO se poznĂˇ tak, Ĺľe v hlasovani_poslanec.vysledek = 'A'.
SELECT *
FROM osoba
WHERE NOT EXISTS (SELECT 1
                  FROM hlasovani
                           JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                           JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                           JOIN organ ON hlasovani.id_organ = organ.id_organ
                  WHERE nazev_dlouhy LIKE 'NĂˇvrh na vyslovenĂ­ nedĹŻvÄ›ry vlĂˇdÄ›%'
                    AND YEAR(organ.od_organ) = 2017
                    AND hp.vysledek = 'A'
                    AND poslanec.id_osoba = osoba.id_osoba)
  AND EXISTS (SELECT 1
              FROM hlasovani
                       JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                       JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                       JOIN organ ON hlasovani.id_organ = organ.id_organ
              WHERE nazev_dlouhy LIKE 'NĂˇvrh na vyslovenĂ­ nedĹŻvÄ›ry vlĂˇdÄ›%'
                AND YEAR(organ.od_organ) = 2017
                AND poslanec.id_osoba = osoba.id_osoba)
ORDER BY id_osoba


-- B

-------------
-- 1. NaleznÄ›te volebnĂ­ obdobĂ­, ve kterĂ©m byly v poslaneckĂ© snÄ›movnÄ› alespoĹ dva kluby s minimĂˇlnÄ› 50 poslanci
-- (staÄŤĂ­ poÄŤet zĂˇznamĹŻ v tabulce poslanec pro danĂ© obdobĂ­).
-- VypiĹˇte id volebnĂ­ho obdobĂ­ (id_organ), kdy volebnĂ­ obdobĂ­ zaÄŤĂ­nalo a poÄŤet klubĹŻ s vĂ­ce neĹľ 50 poslanci.
-- PoslaneckĂ˝ klub je zĂˇznam v organ pro kterĂ˝ typ_organu.nazev_typ_org_cz = 'klub'.
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
HAVING COUNT(*) >= 2


------
-- 2. Pro kaĹľdou schĹŻzi ve volebnĂ­m obdobĂ­ 2002 - 2006 naleznÄ›te poslednĂ­ hlasovĂˇnĂ­.
-- K porovnĂˇnĂ­ poĹ™adĂ­ mĹŻĹľete vyuĹľĂ­t atribut hlasovani.cislo. 
-- Tzn. zajĂ­mĂˇ nĂˇs hlasovĂˇnĂ­ s nejvyĹˇĹˇĂ­ hodnotou atributu hlasovani.cislo v rĂˇmci jednĂ© schĹŻze.
-- SetĹ™iÄŹte vĂ˝sledek podle atributu schuze.schuze a vypiĹˇte atributy id_hlasovani, schuze, cislo a schuze.nazev_dlouhy.
WITH tab AS (SELECT hlasovani.*
             FROM schuze
                      JOIN hlasovani ON schuze.schuze = hlasovani.schuze AND
                                        schuze.id_organ = hlasovani.id_organ
                      JOIN organ ON organ.id_organ = schuze.id_organ
             WHERE YEAR(organ.od_organ) = 2002)
SELECT id_hlasovani, schuze, cislo, nazev_dlouhy
FROM tab t1
WHERE t1.cislo >= ALL (SELECT cislo
                       FROM tab t2
                       WHERE t1.schuze = t2.schuze)
ORDER BY t1.schuze


SELECT hlasovani.*
FROM schuze
         JOIN hlasovani ON schuze.schuze = hlasovani.schuze AND
                           schuze.id_organ = hlasovani.id_organ
         JOIN organ ON organ.id_organ = schuze.id_organ
WHERE YEAR(organ.od_organ) = 2002
  AND schuze.schuze = 1


------
-- 3. NaleznÄ›te osoby, kterĂ© nikdy ve volebnĂ­m obdobĂ­ 2017 - 2021 nehlasovaly PRO u hlasovĂˇnĂ­,
-- jehoĹľ dlouhĂ˝ nĂˇzev (t.j. hlasovani.nazev_dlouhy) obsahuje "COVID".
-- Vyberte pouze osoby, kterĂ© hlasovaly v nÄ›jakĂ© takovĂ©m hlasovĂˇnĂ­, ale nikdy nehlasovali PRO.
-- VypiĹˇte vĹˇechny Ăşdaje osoby a setĹ™iÄŹte je podle id_osoba.
-- HlasovĂˇnĂ­ PRO se poznĂˇ tak, Ĺľe v hlasovani_poslanec.vysledek = 'A'.
SELECT *
FROM osoba
WHERE NOT EXISTS (SELECT 1
                  FROM hlasovani
                           JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                           JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                           JOIN organ ON hlasovani.id_organ = organ.id_organ
                  WHERE nazev_dlouhy LIKE '%COVID%'
                    AND YEAR(organ.od_organ) = 2017
                    AND hp.vysledek = 'A'
                    AND poslanec.id_osoba = osoba.id_osoba)
  AND EXISTS (SELECT 1
              FROM hlasovani
                       JOIN hlasovani_poslanec hp ON hlasovani.id_hlasovani = hp.id_hlasovani
                       JOIN poslanec ON poslanec.id_poslanec = hp.id_poslanec
                       JOIN organ ON hlasovani.id_organ = organ.id_organ
              WHERE nazev_dlouhy LIKE '%COVID%'
                AND YEAR(organ.od_organ) = 2017
                AND poslanec.id_osoba = osoba.id_osoba)


----------------------------------------------------
----------------------------------------------------
-- StĹ™eda 9:00

-- A


-- A

-- PĹ™Ă­klad 1: VypiĹˇte osoby, kterĂ© byly jmenovĂˇny do VlĂˇdy ÄŚR 
-- (organ.nazev_organu_cz like 'VlĂˇda ÄŚeskĂ© republiky') v obdobĂ­ PoslaneckĂ© snÄ›movny 
-- (organ.nazev_organu_cz like 'PoslaneckĂˇ snÄ›movna'), aniĹľ by zĂ­skaly mandĂˇt ve 
-- volbĂˇch v tomto obdobĂ­ poslaneckĂ© snÄ›movny.
-- Pro kaĹľdou osobu vypiĹˇte:
--   id_osoba, jmĂ©no a pĹ™Ă­jmenĂ­, poÄŤet takovĂ˝ch jmenovĂˇnĂ­, poÄŤet mÄ›sĂ­cĹŻ ve vlĂˇdÄ›
--   pro takovĂˇ jmenovĂˇnĂ­.
-- SetĹ™iÄŹte dle poÄŤtu takovĂ˝ch jmenovĂˇnĂ­. UvaĹľujte pouze osoby, kterĂ©
-- byly takto jmenovĂˇny nejmĂ©nÄ› 3x.

SELECT o1.id_osoba,
       o1.jmeno,
       o1.prijmeni,
       COUNT(*)                               AS pocet_jmenovani,
       SUM(DATEDIFF(MONTH, z1.od_o, z1.do_o)) AS pocet_mesicu_ve_vlade
FROM osoba o1
         JOIN zarazeni z1 ON o1.id_osoba = z1.id_osoba
         JOIN organ org1 ON z1.id_of = id_organ AND z1.cl_funkce = 0
WHERE org1.nazev_organu_cz LIKE 'VlĂˇda ÄŚeskĂ© republiky'
  AND NOT EXISTS
    (SELECT 1
     FROM osoba o2
              JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
              JOIN organ org2 ON z2.id_of = org2.id_organ AND z2.cl_funkce = 0
     WHERE org2.nazev_organu_cz LIKE 'PoslaneckĂˇ snÄ›movna'
       AND (o1.id_osoba = o2.id_osoba AND z1.od_o BETWEEN org2.od_organ AND org2.do_organ))
GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni
HAVING COUNT(*) > 2
ORDER BY pocet_jmenovani DESC

/*
VĂ˝sledek: 2 zĂˇznamy
id_osoba	jmeno	prijmeni	pocet_jmenovani	pocet_mesicu_ve_vlade
5326	Milan	Ĺ imonovskĂ˝	3	49
5524	Alexandr	Vondra	3	61
*/

---------------------------------------------------------------------------------------

-- PĹ™Ă­klad 2: VypiĹˇte osoby (id_osoba, jmeno a pĹ™Ă­jmenĂ­), kterĂ© se ÄŤastÄ›ji omlouvaly v lednu 
-- neĹľ v Ăşnoru a zĂˇroveĹ poÄŤet omluv v lednu > 33. 
-- SetĹ™iÄŹte sestupnÄ› dle poÄŤtu omluv v lednu.

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
ORDER BY t.pocet_dnu_leden DESC

/*
VĂ˝sledek: 7 zĂˇznamĹŻ
id_osoba	jmeno	prijmeni	pocet_dnu_leden	pocet_dnu_unor
6168	Helena	VĂˇlkovĂˇ	55	36
6150	Andrej	BabiĹˇ	54	31
6138	Pavel	BÄ›lobrĂˇdek	44	35
6505	Julius	Ĺ piÄŤĂˇk	39	17
401	Miroslava	NÄ›mcovĂˇ	36	12
6166	Jan	VolnĂ˝	35	33
6200	Milan	Chovanec	35	21
*/

---------------------------------------------------------------------------------------

-- PĹ™Ă­klad 3: VypiĹˇte osoby, kterĂ© byly mĂ­stopĹ™edsedou snÄ›movny (typ_funkce.typ_funkce_cz='MĂ­stopĹ™edseda',
-- typ_organu.nazev_typ_org_cz='Parlament') vĂ­ce neĹľ jednou. Pro kaĹľdou osobu uveÄŹte:
--   id_osoba, jmĂ©no, pĹ™Ă­jmenĂ­, poÄŤet tÄ›chto funkcĂ­, poÄŤet ÄŤlenstvĂ­ v delegacĂ­ch
--   (typ_organu.nazev_typ_org_cz='Delegace'). 
-- SetĹ™iÄŹte sestupnÄ› dle poÄŤtu mĂ­stopĹ™esednickĂ© funkce.

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
WHERE tf.typ_funkce_cz = 'MĂ­stopĹ™edseda'
  AND tor.nazev_typ_org_cz = 'Parlament'
GROUP BY o.id_osoba, o.jmeno, o.prijmeni
HAVING COUNT(*) > 1
ORDER BY pocet DESC

/*
VĂ˝sledek: 10 zĂˇznamĹŻ
id_osoba	jmeno	prijmeni	pocet	pocet_clenstvi_delegace
64	Jan	Kasal	4	3
303	VojtÄ›ch	Filip	4	1
401	Miroslava	NÄ›mcovĂˇ	2	5
5462	Jan	HamĂˇÄŤek	2	4
89	Karel	Ledvinka	2	0
6178	Jan	BartoĹˇek	2	0
16	Petra	BuzkovĂˇ	2	0
181	JiĹ™Ă­	Vlach	2	1
252	LubomĂ­r	ZaorĂˇlek	2	1
266	Ivan	Langer	2	1
*/


-- B

-- PĹ™Ă­klad 1: VypiĹˇte osoby, kterĂ© byly v nÄ›jakĂ©m vĂ˝boru poslaneckĂ© snÄ›movny 
-- (typ_organ.nazev_typ_org_cz='VĂ˝bor') a zĂˇroveĹ ve stejnĂ©m volebnĂ­m obdobĂ­
-- (tj. orgĂˇny majĂ­ stejnou hodnotu organ.rodic_id_organ) nebyly 
-- v ĹľĂˇdnĂ© delegaci poslaneckĂ© snÄ›movny (typ_organ.nazev_typ_org_cz='Delegace').
-- Pro kaĹľdou osobu vypiĹˇte:
--   id_osoba, jmĂ©no a pĹ™Ă­jmenĂ­ osoby, poÄŤet takovĂ˝ch ÄŤlenstvĂ­ ve vĂ˝borech, 
--   poÄŤet vĹˇech ÄŤlenstvĂ­ v delegacĂ­ch (pokud nebyl poslanec ÄŤlenem ĹľĂˇdnĂ© delegace,
--   vypiĹˇte hodnotu 0).
-- SetĹ™iÄŹte dle poÄŤtu ÄŤlenstvĂ­ ve vĹˇech delegacĂ­ch. 
-- UvaĹľujte pouze osoby, kterĂ© byly ÄŤleny takovĂ˝ch vĂ˝borĹŻ 8x.

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
WHERE tor1.nazev_typ_org_cz = 'VĂ˝bor'
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

/*
VĂ˝sledek: 25 zĂˇznamĹŻ
id_osoba	jmeno	prijmeni	pocet_vybor	pocet_delegace
5379	Jan	Bauer	8	2
252	LubomĂ­r	ZaorĂˇlek	8	1
261	ZdeĹka	HornĂ­kovĂˇ	8	1
356	Michal	Doktor	8	0
415	Pavel	SuchĂˇnek	8	0
...
*/

-----------------------------------------------------------------------------------

-- PĹ™Ă­klad 2: VypiĹˇte osoby (id_osoba, jmĂ©no, pĹ™Ă­jmenĂ­) aktuĂˇlnĂ­ snÄ›movny (rok organ.od_organ je 2021), 
-- kterĂ© se ÄŤastÄ›ji omlouvaly v dubnu neĹľ v kvÄ›tnu a zĂˇroveĹ poÄŤet omluv v dubnu > 11. 
-- SetĹ™iÄŹte sestupnÄ› dle poÄŤtu omluv v dubnu.

SELECT *
FROM (SELECT os.id_osoba,
             os.jmeno,
             os.prijmeni,
             COUNT(CASE WHEN MONTH(om.den) = 4 THEN 1 END) AS pocet_dnu_duben,
             COUNT(CASE WHEN MONTH(om.den) = 5 THEN 1 END) AS pocet_dnu_kveten
      FROM osoba os
               JOIN poslanec p ON os.id_osoba = p.id_osoba
               JOIN omluva om ON om.id_poslanec = p.id_poslanec
               JOIN organ org ON om.id_organ = org.id_organ
      WHERE YEAR(org.od_organ) = 2021
      GROUP BY os.id_osoba, os.jmeno, os.prijmeni) t
WHERE t.pocet_dnu_duben > 11
  AND t.pocet_dnu_duben > t.pocet_dnu_kveten
ORDER BY t.pocet_dnu_duben DESC

/*
VĂ˝sledek: 6 zĂˇznamĹŻ
id_osoba	jmeno	prijmeni	pocet_dnu_duben	pocet_dnu_kveten
6074	Petr	Fiala	14	12
6168	Helena	VĂˇlkovĂˇ	13	9
6435	Martin	Baxa	13	10
6747	Martin	Exner	13	4
6757	Ĺ imon	Heller	13	12
6523	Michal	RatiborskĂ˝	12	3
*/

-----------------------------------------------------------------------------------

-- PĹ™Ă­klad 3: VypiĹˇte osoby, kterĂ© byly ÄŤleny ĂšstavnÄ› prĂˇvnĂ­ho vĂ˝boru 
-- (organ.nazev_organu_cz je 'ĂšstavnÄ› prĂˇvnĂ­ vĂ˝bor' nebo 'ĂšstavnÄ›-prĂˇvnĂ­ vĂ˝bor') 
-- vĂ­ce neĹľ 3x. Pro kaĹľdou osobu vypiĹˇte:
--   id_osoba, jmĂ©no, pĹ™Ă­jmenĂ­, poÄŤet ÄŤlenstvĂ­ ve vĂ˝boru, celkovĂ˝ poÄŤet ÄŤlenstvĂ­ 
--   v jakĂ©mkoli vĂ˝boru  (typ_organu.nazev_typ_org_cz='VĂ˝bor'). 
-- SetĹ™iÄŹte sestupnÄ› dle poÄŤtu v ĂšstavnÄ› prĂˇvnĂ­m vĂ˝boru.

SELECT o.id_osoba,
       o.jmeno,
       o.prijmeni,
       COUNT(*)                         AS pocet_up_vybor,
       (SELECT COUNT(*)
        FROM osoba o2
                 JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
                 JOIN organ org2 ON z2.id_of = org2.id_organ AND z2.cl_funkce = 0
                 JOIN typ_organu tor2 ON org2.id_typ_org = tor2.id_typ_org
        WHERE tor2.nazev_typ_org_cz = 'VĂ˝bor'
          AND o2.id_osoba = o.id_osoba) AS pocet_clenstvi_ve_vyborech
FROM osoba o
         JOIN zarazeni z ON o.id_osoba = z.id_osoba
         JOIN organ org ON z.id_of = org.id_organ AND z.cl_funkce = 0
WHERE org.nazev_organu_cz = 'ĂšstavnÄ› prĂˇvnĂ­ vĂ˝bor'
   OR org.nazev_organu_cz = 'ĂšstavnÄ›-prĂˇvnĂ­ vĂ˝bor'
GROUP BY o.id_osoba, o.jmeno, o.prijmeni
HAVING COUNT(*) > 3
ORDER BY pocet_up_vybor DESC

/*
VĂ˝sledek: 5 zĂˇznamĹŻ
id_osoba	jmeno	prijmeni	pocet_up_vybor	pocet_clenstvi_ve_vyborech
4	Marek	Benda	9	27
218	ZdenÄ›k	JiÄŤĂ­nskĂ˝	4	6
386	Stanislav	KĹ™eÄŤek	4	12
4778	Stanislav	GrospiÄŤ	4	7
6168	Helena	VĂˇlkovĂˇ	4	11
*/


----------------------------------------------------
----------------------------------------------------
-- StĹ™eda 10:45


-- A

-- PĹ™Ă­klad 1: VypiĹˇte osoby, kterĂ© byly ve stejnĂ©m volebnĂ­m obdobĂ­ poslaneckĂ© snÄ›movny
-- ÄŤleny poslaneckĂ©ho klubu Unie svobody (organ.nazev_organu_cz='PoslaneckĂ˝ klub Unie svobody')
-- a ve stejnĂ©m volebnĂ­m obdobĂ­ (tj. orgĂˇny poslaneckĂ˝ch klubĹŻ majĂ­ stejnou hodnotu organ.rodic_id_organ) 
-- nebyly ÄŤleny poslaneckĂ©ho klubu ObÄŤanskĂ© demokratickĂ© strany
-- (organ.nazev_organu_cz='PoslaneckĂ˝ klub ObÄŤanskĂ© demokratickĂ© strany').
-- Pro kaĹľdou osobu vypiĹˇte:
-- id_osoba, jmeno, prijmenĂ­, poÄŤet mÄ›sĂ­cĹŻ poslaneckĂ©ho mandĂˇtu odpovĂ­dajĂ­cĂ­ho vĂ˝Ĺˇe popsanĂ© podmĂ­nce,
-- celkovĂ˝ poÄŤet mÄ›sĂ­cĹŻ v poslaneckĂ© snÄ›movnÄ›.
-- SetĹ™iÄŹte dle pĹ™Ă­jmenĂ­.

SELECT o1.id_osoba,
       o1.jmeno,
       o1.prijmeni,
       SUM(DATEDIFF(MONTH, z1.od_o, z1.do_o)) AS pocet_mesicu_us,
       (SELECT SUM(DATEDIFF(MONTH, z2.od_o, z2.do_o)) AS pocet_mesicu_ods
        FROM osoba o2
                 JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
                 JOIN organ org2 ON z2.id_of = org2.id_organ AND z2.cl_funkce = 0
        WHERE org2.nazev_organu_cz = 'PoslaneckĂˇ snÄ›movna'
          AND o2.id_osoba = o1.id_osoba
        GROUP BY o2.id_osoba)                 AS pocet_mesicu_poslanec
FROM osoba o1
         JOIN zarazeni z1 ON o1.id_osoba = z1.id_osoba
         JOIN organ org1 ON z1.id_of = org1.id_organ AND z1.cl_funkce = 0
WHERE org1.nazev_organu_cz = 'PoslaneckĂ˝ klub Unie svobody'
  AND NOT EXISTS (SELECT o3.id_osoba, o3.jmeno, o3.prijmeni
                  FROM osoba o3
                           JOIN zarazeni z3 ON o3.id_osoba = z3.id_osoba
                           JOIN organ org3 ON z3.id_of = org3.id_organ AND z3.cl_funkce = 0
                  WHERE org3.nazev_organu_cz = 'PoslaneckĂ˝ klub ObÄŤanskĂ© demokratickĂ© strany'
                    AND o3.id_osoba = o1.id_osoba
                    AND org3.rodic_id_organ = org1.rodic_id_organ)
GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni
ORDER BY o1.prijmeni

/*
VĂ˝sledek: 22 zĂˇznamĹŻ
id_osoba	jmeno	prijmeni	pocet_mesicu_us	pocet_mesicu_poslanec
38	Andrej	GjuriÄŤ	4	53
364	Ivana	HanaÄŤĂ­kovĂˇ	48	48
380	Ladislav	Korbel	48	48
381	ZdenÄ›k	KoĹ™istka	48	71
79	VĂˇclav	KrĂˇsa	48	120
...
*/

---------------------------------------------------------------------------

-- PĹ™Ă­klad 2: VypiĹˇte osoby poslaneckĂ©ho klubu ODS 
-- (organ.nazev_organu_cz='PoslaneckĂ˝ klub ObÄŤanskĂ© demokratickĂ© strany',
-- kterĂ© se ÄŤastÄ›ji omlouvaly v listopadu neĹľ v prosinci a zĂˇroveĹ poÄŤet omluv v listopadu > 16. 
-- SetĹ™iÄŹte sestupnÄ› dle poÄŤtu omluv v listopadu.

SELECT *
FROM (SELECT os.id_osoba,
             os.jmeno,
             os.prijmeni,
             COUNT(CASE WHEN MONTH(om.den) = 11 THEN 1 END) AS pocet_dnu_listopad,
             COUNT(CASE WHEN MONTH(om.den) = 12 THEN 1 END) AS pocet_dnu_prosinec
      FROM osoba os
               JOIN poslanec p ON os.id_osoba = p.id_osoba
               JOIN omluva om ON om.id_poslanec = p.id_poslanec
      WHERE os.id_osoba IN (SELECT z.id_osoba
                            FROM zarazeni z
                                     JOIN organ org ON z.id_of = org.id_organ AND z.cl_funkce = 0
                            WHERE org.nazev_organu_cz = 'PoslaneckĂ˝ klub ObÄŤanskĂ© demokratickĂ© strany')
      GROUP BY os.id_osoba, os.jmeno, os.prijmeni) t
WHERE t.pocet_dnu_listopad > 16
  AND t.pocet_dnu_listopad > t.pocet_dnu_prosinec
ORDER BY t.pocet_dnu_listopad DESC

/*
VĂ˝sledek: 7 zĂˇznamĹŻ
id_osoba	jmeno	prijmeni	pocet_dnu_listopad	pocet_dnu_prosinec
6538	Martin	Kupka	24	21
6467	Zuzana	MajerovĂˇ ZahradnĂ­kovĂˇ	19	12
*/

---------------------------------------------------------------------------

-- PĹ™Ă­klad 3: VypiĹˇte osoby, kterĂ© byly vĂ­ce neĹľ ĹˇestkrĂˇt ÄŤleny poslaneckĂ©ho klubu 
-- (typ_organu.nazev_typ_org_cz='Klub') se stejnĂ˝m nĂˇzvem (tzn. se stejnou 
-- hodnotou organ.nazev_organu_cz). Pro kaĹľdou osobu vypiĹˇte:
--   id_osoba, jmĂ©no, pĹ™Ă­jmenĂ­, nĂˇzev poslaneckĂ©ho klubu, poÄŤet
--   ÄŤlenstvĂ­ v poslaneckĂ©m klubu, poÄŤet obdobĂ­ snÄ›movny ve kterĂ˝ch byla osoba 
--   poslancem. 
-- SetĹ™iÄŹte sestupnÄ› dle poÄŤtu ÄŤlenstvĂ­.

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

/*
VĂ˝sledek: 6 zĂˇznamĹŻ
id_osoba	jmeno	prijmeni	nazev_organu_cz	pocet_klubu	pocet_volebnich_obdobi
4	Marek	Benda	PoslaneckĂ˝ klub ObÄŤanskĂ© demokratickĂ© strany	9	9
237	Bohuslav	Sobotka	PoslaneckĂ˝ klub ÄŚeskĂ© strany sociĂˇlnÄ› demokratickĂ©	7	7
252	LubomĂ­r	ZaorĂˇlek	PoslaneckĂ˝ klub ÄŚeskĂ© strany sociĂˇlnÄ› demokratickĂ©	7	7
303	VojtÄ›ch	Filip	PoslaneckĂ˝ klub KomunistickĂ© strany ÄŚech a Moravy	7	7
305	Miroslav	GrebenĂ­ÄŤek	PoslaneckĂ˝ klub KomunistickĂ© strany ÄŚech a Moravy	7	7
309	Pavel	KovĂˇÄŤik	PoslaneckĂ˝ klub KomunistickĂ© strany ÄŚech a Moravy	7	7
*/


-- B

-- PĹ™Ă­klad 1: VypiĹˇte osoby, kterĂ© byly/jsou ÄŤleny poslaneckĂ©ho klubu TOP 09 
-- (organ.nazev_organu_cz='PoslaneckĂ˝ klub TOP 09')
-- a nebyly ÄŤleny poslaneckĂ©ho klubu ObÄŤanskĂ© demokratickĂ© strany
-- (organ.nazev_organu_cz='PoslaneckĂ˝ klub ObÄŤanskĂ© demokratickĂ© strany')
-- ve stejnĂ©m volebnĂ­m obdobĂ­ (tj. orgĂˇny poslaneckĂ˝ch klubĹŻ majĂ­ stejnou hodnotu 
-- organ.rodic_id_organ).
-- Pro kaĹľdou osobu vypiĹˇte:
--   id_osoba, jmĂ©no, pĹ™Ă­jmenĂ­, poÄŤet mÄ›sĂ­cĹŻ poslaneckĂ©ho mandĂˇtu v TOP 09 (v pĹ™Ă­padÄ›
--   poslaneckĂ©ho mandĂˇtu jen v aktuĂˇlnĂ­m nedokonÄŤenĂ©m obdobĂ­, vypiĹˇte poÄŤet mÄ›sĂ­cĹŻ
--   od zaÄŤĂˇtku mandĂˇtu k aktuĂˇlnĂ­mu datu).
-- SetĹ™iÄŹte dle pĹ™Ă­jmenĂ­.

SELECT o1.id_osoba,
       o1.jmeno,
       o1.prijmeni,
       COALESCE(SUM(DATEDIFF(MONTH, z1.od_o, z1.do_o)),
                SUM(DATEDIFF(MONTH, z1.od_o, GETDATE()))) AS pocet_mesicu_top09
FROM osoba o1
         JOIN zarazeni z1 ON o1.id_osoba = z1.id_osoba
         JOIN organ org1 ON z1.id_of = org1.id_organ AND z1.cl_funkce = 0
WHERE org1.nazev_organu_cz = 'PoslaneckĂ˝ klub TOP 09'
  AND NOT EXISTS (SELECT 1
                  FROM osoba o2
                           JOIN zarazeni z2 ON o2.id_osoba = z2.id_osoba
                           JOIN organ org2 ON z2.id_of = org2.id_organ AND z2.cl_funkce = 0
                  WHERE o2.id_osoba = o1.id_osoba
                    AND org2.nazev_organu_cz = 'PoslaneckĂ˝ klub ObÄŤanskĂ© demokratickĂ© strany'
                    AND org2.rodic_id_organ = org1.rodic_id_organ)
GROUP BY o1.id_osoba, o1.jmeno, o1.prijmeni
ORDER BY pocet_mesicu_top09 DESC

/*
VĂ˝sledek: 19 zĂˇznamĹŻ
id_osoba	jmeno	prijmeni	pocet_mesicu_top09
5558	Karel	Schwarzenberg	48
5943	Helena	LangĹˇĂˇdlovĂˇ	48
6137	FrantiĹˇek	VĂˇcha	48
6147	MarkĂ©ta	PekarovĂˇ AdamovĂˇ	48
...
6802	Pavel	Svoboda	24
6687	Jan	Jakob	9
6707	Olga	SommerovĂˇ	5
*/

-------------------------------------------------------------------------

-- PĹ™Ă­klad 2: VypiĹˇte osoby, kterĂ© se ÄŤastÄ›ji omlouvaly v prvnĂ­ polovinÄ› roku 2021 neĹľ ve druhĂ© 
-- polovinÄ› roku 2021 a zĂˇroveĹ poÄŤet omluv v prvnĂ­ polovinÄ› roku > 47. 
-- SetĹ™iÄŹte sestupnÄ› dle poÄŤtu omluv v prvnĂ­ polovinÄ› roku.

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

/*
VĂ˝sledek: 8 zĂˇznamĹŻ
id_osoba	jmeno	prijmeni	pocet_dnu_1_6	pocet_dnu_7_12
6465	Lenka	KozlovĂˇ	56	13
5558	Karel	Schwarzenberg	54	14
6502	Jana	LevovĂˇ	54	17
5462	Jan	HamĂˇÄŤek	51	18
6147	MarkĂ©ta	PekarovĂˇ AdamovĂˇ	50	10
6150	Andrej	BabiĹˇ	50	18
6074	Petr	Fiala	48	8
6467	Zuzana	MajerovĂˇ ZahradnĂ­kovĂˇ	48	15
*/

-------------------------------------------------------------------------

-- PĹ™Ă­klad 3: VypiĹˇte osoby, kterĂ© v aktuĂˇlnĂ­m volebnĂ­m obdobĂ­ zmÄ›nily poslaneckĂ˝ klub 
-- (typ_organu.nazev_typ_org_cz='Klub'), tedy jsou/byly ÄŤleny vĂ­ce neĹľ jednoho poslaneckĂ©ho klubu. 
-- Pro kaĹľdou osobu vypiĹˇte:
--   id_osoba, jmĂ©no, pĹ™Ă­jmenĂ­, poÄŤet poslaneckĂ˝ch klubĹŻ v aktuĂˇlnĂ­m volebnĂ­m obdobĂ­, 
--   poÄŤet mÄ›sĂ­cĹŻ v poslaneckĂ˝ch klubech s ukonÄŤenĂ˝m ÄŤlenstvĂ­m v aktuĂˇlnĂ­m volebnĂ­m obdobĂ­. 
-- SetĹ™iÄŹte sestupnÄ› dle poÄŤtu klubĹŻ.
-- 
-- PoznĂˇmka: organ.od_organ poslaneckĂ©ho klubu musĂ­ bĂ˝t mezi organ.od_organ a organ.do_organ
-- orgĂˇnu obdobĂ­ poslaneckĂ© snÄ›movny.

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

/*
VĂ˝sledek: 1 zĂˇznam
id_osoba	jmeno	prijmeni	pocet_ruznych_klubu	pocet_mesicu_ukoncenych_clenstvi
6492	Ivo	VondrĂˇk	2	16
*/