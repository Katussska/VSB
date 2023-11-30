SELECT COUNT(1)
FROM schuze
         JOIN hlasovani ON schuze.schuze = hlasovani.schuze
    AND
                           hlasovani.id_organ = schuze.id_organ


--NOT IN (168, 169, 170, 171, 172)

SELECT COUNT(1), id_organ
FROM hlasovani
GROUP BY id_organ

SELECT *
FROM organ


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