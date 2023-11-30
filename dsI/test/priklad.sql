SELECT id_hlasovani,
       datum,
       nazev_dlouhy,
       id_organ,
       (SELECT COUNT(1)
        FROM hlasovani_poslanec
                 JOIN dbo.poslanec p ON hlasovani_poslanec.id_poslanec = p.id_poslanec
                 JOIN zarazeni ON p.id_osoba = zarazeni.id_osoba AND zarazeni.cl_funkce = 0
                 JOIN organ ON zarazeni.id_of = organ.id_organ AND organ.zkratka = 'ODS'
                 JOIN organ org2 ON organ.rodic_id_organ = org2.id_organ AND org2.id_organ = hlasovani.id_organ
        WHERE hlasovani_poslanec.vysledek = 'A'
          AND hlasovani_poslanec.id_hlasovani = hlasovani.id_hlasovani) AS odsPro,
       (SELECT COUNT(1)
        FROM hlasovani_poslanec
                 JOIN dbo.poslanec p ON hlasovani_poslanec.id_poslanec = p.id_poslanec
                 JOIN zarazeni ON p.id_osoba = zarazeni.id_osoba AND zarazeni.cl_funkce = 0
                 JOIN organ ON zarazeni.id_of = organ.id_organ AND organ.zkratka = 'ANO'
                 JOIN organ org2 ON organ.rodic_id_organ = org2.id_organ AND org2.id_organ = hlasovani.id_organ
        WHERE hlasovani_poslanec.vysledek = 'A'
          AND hlasovani_poslanec.id_hlasovani = hlasovani.id_hlasovani) AS anoPro
FROM hlasovani
WHERE hlasovani.cislo = 172
  AND hlasovani.datum = '2019-10-24'

SELECT *
FROM organ

SELECT id_organ
FROM poslanec
GROUP BY id_organ

SELECT id_of, id_organ, COUNT(1)
FROM zarazeni
         JOIN organ ON zarazeni.id_of = organ.id_organ
WHERE cl_funkce = 0
GROUP BY id_of, id_organ