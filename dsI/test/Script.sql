/*select o1.id_osoba, o1.jmeno, o1.prijmeni,
  sum(datediff(month, z1.od_o, z1.do_o)) as pocet_mesicu_us,
  (
    select sum(datediff(month, z2.od_o, z2.do_o)) as pocet_mesicu_ods from osoba o2
    join zarazeni z2 on o2.id_osoba=z2.id_osoba
    join organ org2 on z2.id_of=org2.id_organ and z2.cl_funkce=0
    where org2.nazev_organu_cz='Poslanecká sněmovna' and o2.id_osoba=o1.id_osoba
	group by o2.id_osoba
  ) as pocet_mesicu_poslanec
from osoba o1
join zarazeni z1 on o1.id_osoba=z1.id_osoba
join organ org1 on z1.id_of=org1.id_organ and z1.cl_funkce=0
where org1.nazev_organu_cz='Poslanecký klub Unie svobody'
and not exists (
  select o3.id_osoba, o3.jmeno, o3.prijmeni from osoba o3
  join zarazeni z3 on o3.id_osoba=z3.id_osoba
  join organ org3 on z3.id_of=org3.id_organ and z3.cl_funkce=0
  where org3.nazev_organu_cz='Poslanecký klub Občanské demokratické strany'
        and o3.id_osoba=o1.id_osoba and org3.rodic_id_organ=org1.rodic_id_organ
)
group by o1.id_osoba, o1.jmeno, o1.prijmeni
order by o1.prijmeni*/

SELECT *
FROM (SELECT o.jmeno,
             o.prijmeni,
             COUNT(CASE WHEN MONTH(o3.den) = 11 THEN 'neco' END) AS pocet_dnu_listopad,
             COUNT(CASE WHEN MONTH(o3.den) = 12 THEN 1 END)      AS pocet_dnu_prosinec
      FROM osoba o
               JOIN poslanec p ON p.id_osoba = o.id_osoba
               JOIN omluva o3 ON o3.id_poslanec = p.id_poslanec
      GROUP BY o.jmeno, o.prijmeni) t
WHERE t.pocet_dnu_listopad > 16
  AND t.pocet_dnu_listopad > t.pocet_dnu_prosinec
ORDER BY t.pocet_dnu_listopad DESC


SELECT *
FROM (SELECT o.jmeno, o.prijmeni, org.nazev_organu_cz, COUNT(org.id_typ_org) AS pocet
      FROM osoba o
               JOIN zarazeni z ON z.id_osoba = o.id_osoba
               JOIN organ org ON z.id_of = org.id_organ
      WHERE org.id_typ_org = 1
      GROUP BY o.jmeno, o.prijmeni, org.nazev_organu_cz) t
WHERE t.pocet > 6
ORDER BY t.pocet DESC


SELECT *
FROM (SELECT os.id_osoba,
             os.jmeno,
             os.prijmeni,
             COUNT(CASE WHEN MONTH(o.den) = 1 THEN 'neco' END) AS pocet_leden,
             COUNT(CASE WHEN MONTH(o.den) = 2 THEN 'neco' END) AS pocet_unor
      FROM osoba os
               JOIN poslanec p ON p.id_osoba = os.id_osoba
               JOIN omluva o ON o.id_poslanec = p.id_poslanec
      GROUP BY os.id_osoba, os.jmeno, os.prijmeni) t
WHERE t.pocet_leden > 33
  AND t.pocet_leden > t.pocet_unor
ORDER BY t.pocet_leden DESC


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
WHERE tf.typ_funkce_cz = 'Mí­stopředseda'
  AND tor.nazev_typ_org_cz = 'Parlament'
GROUP BY o.id_osoba, o.jmeno, o.prijmeni
HAVING COUNT(*) > 1
ORDER BY pocet DESC



