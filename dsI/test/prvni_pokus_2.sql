-- PoznĂˇmka: ĹľĂˇdnĂ© ze zde uvedenĂ˝ch Ĺ™eĹˇenĂ­ si nenĂˇrokuje titul "jedinnĂ© sprĂˇvnĂ© Ĺ™eĹˇenĂ­".
-- VĹľdy existuje mnoho variant zĂˇpisu a ideĂˇlnÄ› by jste mÄ›li bĂ˝t schopni to zapsat i jinak nÄ›Ĺľ je uvedeno v Ĺ™eĹˇenĂ­

----------------------------------------------------
----------------------------------------------------
-- PondÄ›lĂ­ 16:00 (LukĂˇĹˇ Moravec)
-- Varianta A

-------------
-- 1. Pro kaĹľdĂ© volebnĂ­ obdobĂ­ vypiĹˇte osobu z ODS, kterĂˇ mÄ›la nejvĂ­ce omluvenek.
-- Za omluvenku povaĹľujeme jeden zĂˇznam v tabulce omluva.
-- Osoba z ODS znamenĂˇ, Ĺľe osoba byla v danĂ©m volebnĂ­m obdobĂ­ zaĹ™azena do organ.zkratka = 'ODS', 
-- kde typ_organu.nazev_typ_org_cz = 'klub'.
-- VypiĹˇte id_osoby, jmĂ©no, pĹ™ijmenĂ­, id_organ volebnĂ­ho obdobĂ­ a interval volebnĂ­ho obdobĂ­ (od_organ, do_organ).
-- SetĹ™iÄŹte podle id_organ volebnĂ­ho obdobĂ­.
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

/*
id_osoba, jmeno, prijmeni, id_organ, od_organ, do_organ pocet_omluvenek
282	OldĹ™ich	VojĂ­Ĺ™	167	1998-06-20	2002-06-20	8
401	Miroslava	NÄ›mcovĂˇ	168	2002-06-15	2006-06-15	30
266	Ivan	Langer	169	2006-06-03	2010-06-03	81
5924	TomĂˇĹˇ	Chalupa	170	2010-05-29	2013-08-28	65
5700	Ivan	Adamec	171	2013-10-26	2017-10-26	72
6467	Zuzana	MajerovĂˇ ZahradnĂ­kovĂˇ	172	2017-10-21	2021-10-20	180
5903	Jana	ÄŚernochovĂˇ	173	2021-10-09	NULL	158
6079	Pavel	BlaĹľek	173	2021-10-09	NULL	158
*/

-------------
-- 2. VypiĹˇte osoby, kterĂ© nÄ›kdy byli v politickĂ©m klubu se zkratkou 'VV' i 'Ăšsvit' (t.j. organ.zkratka).
-- PolitickĂ˝ klub je zĂˇznam v tabulce organ, kterĂ˝ mĂˇ typ_organu.nazev_typ_org_cz = 'klub'.
-- VypiĹˇte id_osoba, jmeno, prijmeni, zkratka klubu, od_organ a do_organ klubu.
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
                     WHERE osoby_v_klubu.zkratka = N'Ăšsvit')
  AND typ_organu.nazev_typ_org_cz = 'klub'

/*
jmeno, prijmeni, zkratka, od_organ, do_organ
David	KĂˇdner	VV	2010-05-31	2013-08-28
David	KĂˇdner	Ăšsvit	2013-11-05	2017-10-26
JiĹ™Ă­	Ĺ tÄ›tina	VV	2010-05-31	2013-08-28
JiĹ™Ă­	Ĺ tÄ›tina	Ăšsvit	2013-11-05	2017-10-26
*/


-------------
-- 3. Pro kaĹľdou schĹŻzi konanou ve volebnĂ­m obdobĂ­ 2017-2021 vypiĹˇte nĂˇsledujĂ­cĂ­ informace:
-- a. id_schuze, schuze, od_schuze, do_schuze
-- b. PrĹŻmÄ›rnĂ˝ poÄŤet hlasovĂˇnĂ­ "proti" (atribut hlasovani.proti, pĹ™eveÄŹte na FLOAT s pomocĂ­ CAST(hh.proti AS FLOAT))
-- c. PoÄŤet hlasovĂˇnĂ­, kterĂ© byly prohlĂˇĹˇeny za zmateÄŤnĂ© (to jsou hlasovani jejichĹľ id_hlasovani nalezneme v tabulce zmatecne)
-- d. PoÄŤet zĂˇznamu, kterĂ© je moĹľnĂ© ke schĹŻzi nalĂ©zt v tabulce schuze_bod a kterĂ© majĂ­ id_bod_stav = 1.
-- Vemte do Ăşvahy, Ĺľe jedno hlasovĂˇnĂ­ mĹŻĹľe bĂ˝t uvedeno v tabulce zmatecne vĂ­cekrĂˇt.
-- NezapomÄ›Ĺte, Ĺľe tabulka schuze a hlasovani se spojuje na zĂˇkladÄ› rovnosti dvou atributĹŻ: schuze a id_organ.
-- Naopak tabulka schuze a bod_schuze se spojujĂ­ na zĂˇkladÄ› id_schuze.
-- SetĹ™iÄŹte vĂ˝sledek podle id_schuze.
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

/*
120 vĂ˝sledkĹŻ
id_schuze, schuze, od_schuze, do_schuze, prumerny_pocet_proti, zmatecne_hlasovani, pocet_bodu
469	1	2017-11-20 13:00:00.0000000	2017-11-24 14:09:00.0000000	25.625	1	19
470	2	2017-11-28 14:00:00.0000000	2017-11-30 11:00:00.0000000	23.6351351351351	4	35
473	3	2017-12-05 14:00:00.0000000	2017-12-05 19:40:00.0000000	31.3333333333333	0	6
474	4	2017-12-12 14:00:00.0000000	2017-12-19 22:00:00.0000000	56.625	2	29
475	5	2018-01-10 10:00:00.0000000	2018-01-16 16:15:00.0000000	65.625	0	5
476	6	2018-01-17 09:00:00.0000000	2018-01-26 09:25:00.0000000	21.3068181818182	0	39
477	7	2018-02-27 14:00:00.0000000	2018-03-21 18:20:00.0000000	21.8562091503268	3	16
478	12	2018-04-10 14:00:00.0000000	2018-04-20 13:30:00.0000000	18.8811188811189	2	80
480	8	2018-03-09 09:00:00.0000000	2018-03-09 12:45:00.0000000	9	0	3
481	9	2018-03-07 14:30:00.0000000	2018-03-07 16:17:00.0000000	22.5	0	3
482	10	2018-03-27 14:00:00.0000000	2018-03-27 14:31:00.0000000	NULL	0	3
483	11	2018-03-27 15:30:00.0000000	2018-03-27 16:50:00.0000000	23.75	0	3
484	21	2018-11-14 14:30:00.0000000	2018-11-14 15:05:00.0000000	NULL	0	4
485	13	2018-05-22 14:00:00.0000000	2018-06-13 17:53:00.0000000	22.8974358974359	5	120
486	14	2018-05-31 09:00:00.0000000	2020-06-04 20:55:00.0000000	16	0	4
487	15	2018-06-14 09:00:00.0000000	2018-06-14 11:14:00.0000000	1.5	0	4
...
*/


-- Varianta B

-------------
-- 1. Pro kaĹľdĂ© volebnĂ­ obdobĂ­ vypiĹˇte osobu z KSÄŚM, kterĂˇ mÄ›la nejvĂ­ce omluvenek.
-- Za omluvenku povaĹľujeme jeden zĂˇznam v tabulce omluva.
-- Osoba z KSÄŚM znamenĂˇ, Ĺľe osoba byla v danĂ©m volebnĂ­m obdobĂ­ zaĹ™azena do organ.zkratka = 'KSÄŚM', 
-- kde typ_organu.nazev_typ_org_cz = 'klub'.
-- VypiĹˇte id_osoby, jmĂ©no, pĹ™ijmenĂ­, id_organ volebnĂ­ho obdobĂ­ a interval volebnĂ­ho obdobĂ­ (od_organ, do_organ).
-- SetĹ™iÄŹte podle id_organ volebnĂ­ho obdobĂ­.
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
                                   WHERE organ.zkratka = 'KSÄŚM'
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

/*
id_osoba, jmeno, prijmeni, id_organ, od_organ, do_organ pocet_omluvenek
31	VĂˇclav	Exner	167	1998-06-20	2002-06-20	4
5321	KateĹ™ina	KoneÄŤnĂˇ	168	2002-06-15	2006-06-15	40
366	Pavel	Hojda	169	2006-06-03	2010-06-03	29
5768	VojtÄ›ch	Adam	170	2010-05-29	2013-08-28	52
5768	VojtÄ›ch	Adam	171	2013-10-26	2017-10-26	177
5938	KvÄ›ta	MatuĹˇovskĂˇ	172	2017-10-21	2021-10-20	142
*/

-------------
-- 2. VypiĹˇte osoby, kterĂ© nÄ›kdy byli v politickĂ©m klubu se zkratkou 'TOP09-S' i 'Stan' (t.j. organ.zkratka).
-- PolitickĂ˝ klub je zĂˇznam v tabulce organ, kterĂ˝ mĂˇ typ_organu.nazev_typ_org_cz = 'klub'.
-- VypiĹˇte id_osoba, jmeno, prijmeni, zkratka klubu, od_organ a do_organ klubu.
-- SetĹ™iÄŹte podle id_osoba.
WITH osoby_v_klubu AS (SELECT z.id_osoba, org.zkratka
                       FROM zarazeni z
                                JOIN organ org ON z.id_of = org.id_organ AND cl_funkce = 0
                                JOIN typ_organu torg ON org.id_typ_org = torg.id_typ_org
                       WHERE torg.nazev_typ_org_cz = 'klub')
SELECT o.id_osoba, o.jmeno, o.prijmeni, org.zkratka, org.od_organ, org.do_organ
FROM osoba o
         JOIN zarazeni z ON o.id_osoba = z.id_osoba
         JOIN organ org ON z.id_of = org.id_organ
         JOIN typ_organu ON typ_organu.id_typ_org = org.id_typ_org
WHERE o.id_osoba IN (SELECT id_osoba
                     FROM osoby_v_klubu
                     WHERE osoby_v_klubu.zkratka = 'TOP09-S')
  AND o.id_osoba IN (SELECT id_osoba
                     FROM osoby_v_klubu
                     WHERE osoby_v_klubu.zkratka = 'STAN')
  AND typ_organu.nazev_typ_org_cz = 'klub'
ORDER BY o.id_osoba


/*
jmeno, prijmeni, zkratka, od_organ, do_organ
5901	Josef	Cogan	TOP09-S	2010-06-10	2013-08-28
5901	Josef	Cogan	STAN	2021-10-15	NULL
5909	Jan	FarskĂ˝	TOP09-S	2010-06-10	2013-08-28
5909	Jan	FarskĂ˝	TOP09-S	2013-10-31	2017-10-26
5909	Jan	FarskĂ˝	STAN	2017-10-23	2021-10-20
5909	Jan	FarskĂ˝	STAN	2021-10-15	NULL
5914	Petr	GazdĂ­k	TOP09-S	2010-06-10	2013-08-28
5914	Petr	GazdĂ­k	TOP09-S	2013-10-31	2017-10-26
5914	Petr	GazdĂ­k	STAN	2017-10-23	2021-10-20
5914	Petr	GazdĂ­k	STAN	2021-10-15	NULL
6214	VÄ›ra	KovĂˇĹ™ovĂˇ	TOP09-S	2013-10-31	2017-10-26
6214	VÄ›ra	KovĂˇĹ™ovĂˇ	STAN	2017-10-23	2021-10-20
6214	VÄ›ra	KovĂˇĹ™ovĂˇ	STAN	2021-10-15	NULL
*/


-------------
-- 3. Pro kaĹľdou schĹŻzi konanou v aktuĂˇlnĂ­m volebnĂ­m obdobĂ­ vypiĹˇte nĂˇsledujĂ­cĂ­ informace:
-- a. id_schuze, schuze, od_schuze, do_schuze
-- b. PrĹŻmÄ›rnĂ˝ poÄŤet hlasovĂˇnĂ­ "proti" (atribut hlasovani.pro, pĹ™eveÄŹte na FLOAT s pomocĂ­ CAST(hh.pro AS FLOAT))
-- c. PoÄŤet hlasovĂˇnĂ­, ve kterych nehlasovala vic jak 1/4 prihlasenych (vyuĹľijte atributy hlasovani.nehlasoval a hlasovani.prihlaseno)
-- d. PoÄŤet zĂˇznamu, kterĂ© je moĹľnĂ© ke schĹŻzi nalĂ©zt v tabulce schuze_bod a kterĂ© majĂ­ id_bod_stav = 0.
-- NezapomÄ›Ĺte, Ĺľe tabulka schuze a hlasovani se spojuje na zĂˇkladÄ› rovnosti dvou atributĹŻ: schuze a id_organ.
-- SetĹ™iÄŹte podle id_schuze.
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


/*
120 vĂ˝sledkĹŻ
id_schuze, schuze, od_schuze, do_schuze, prumerny_pocet_pro, nehlasovala_ctvrtina, pocet_bodu
629	1	2021-11-08 14:00:00.0000000	2021-11-10 22:35:00.0000000	170	0	17
630	2	2021-11-23 14:00:00.0000000	2021-11-26 10:19:00.0000000	160.753246753247	2	31
633	3	2021-12-01 14:00:00.0000000	2021-12-01 17:03:00.0000000	139.111111111111	3	3
634	4	2021-12-14 14:00:00.0000000	2021-12-14 19:49:00.0000000	135.357142857143	0	9
637	5	2021-12-15 09:00:00.0000000	2021-12-15 12:13:00.0000000	105.5	0	0
638	6	2022-01-11 14:00:00.0000000	2022-01-28 13:10:00.0000000	116.888888888889	13	15
639	7	2022-01-13 09:00:00.0000000	2022-01-13 10:58:00.0000000	117	0	0
642	9	2022-02-15 14:00:00.0000000	2022-03-04 13:24:00.0000000	102.284810126582	0	37
643	8	2022-02-01 10:00:00.0000000	2022-02-02 22:03:00.0000000	59.2931034482759	1	1
645	10	2022-02-17 09:00:00.0000000	2022-02-17 13:46:00.0000000	107	0	0
647	11	2022-02-18 09:00:00.0000000	2022-02-18 21:43:00.0000000	152.666666666667	0	2
...
*/


----------------------------------------------------
----------------------------------------------------
-- PondÄ›lĂ­ 17:45 (LukĂˇĹˇ Moravec)
-- Varianta A

-------------
-- 1. Pro volebnĂ­ obdobĂ­ 2013-2017, naleznÄ›te osobu, kterĂˇ hlasovala nejÄŤastÄ›ji PRO (hlasovani_poslanec.vysledek = 'A')
-- v rĂˇmci poslancĹŻ ze stejnĂ© kandidĂˇtky (poslanec.id_kandidatka).
-- Tzn. v danĂ©m volebnĂ­m obdobĂ­ nenĂ­ osoba z danĂ© kandidĂˇtky, kterĂˇ by hlasovala vĂ­cekrĂˇt 'A'.
-- Do vĂ˝stupu uveÄŹte id_osoba, celĂ© jmĂ©no, pĹ™ijmenĂ­ osoby, id_kandidatka kde byla osoba zaĹ™azena a poÄŤet hlasovĂˇnĂ­ PRO.
-- SetĹ™idte vĂ˝sledek podle id_kandidatka.
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


-----------------
-- 2.
-- VypiĹˇte osoby (id_osoba, jmeno, prijmeni), kterĂ© nÄ›kdy byly ve funkci pĹ™edsedy zahraniÄŤnĂ­ho vĂ˝boru, ale nikdy ve funkci mĂ­stropĹ™edsedy.
-- PĹ™edseda/mĂ­stopĹ™edseda zahraniÄŤnĂ­ho vĂ˝boru je funkce, kterĂˇ mĂˇ typ_funkce.typ_funkce_cz = 'PĹ™edseda'/'MĂ­stopĹ™edseda'
-- a orgĂˇn tĂ©to funkce mĂˇ organ.nazev_organu_cz = N'ZahraniÄŤnĂ­ vĂ˝bor'.
SELECT osoba.id_osoba, jmeno, prijmeni
FROM osoba
WHERE osoba.id_osoba IN (SELECT z.id_osoba
                         FROM zarazeni z
                                  JOIN funkce f ON f.id_funkce = z.id_of AND z.cl_funkce = 1
                                  JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
                                  JOIN organ org ON f.id_organ = org.id_organ
                         WHERE tf.typ_funkce_cz = N'PĹ™edseda'
                           AND nazev_organu_cz = N'ZahraniÄŤnĂ­ vĂ˝bor')
  AND osoba.id_osoba NOT IN (SELECT z.id_osoba
                             FROM zarazeni z
                                      JOIN funkce f ON f.id_funkce = z.id_of AND z.cl_funkce = 1
                                      JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
                                      JOIN organ org ON f.id_organ = org.id_organ
                             WHERE tf.typ_funkce_cz = N'MĂ­stopĹ™edseda'
                               AND nazev_organu_cz = N'ZahraniÄŤnĂ­ vĂ˝bor')

/*
id_osoba jmeno prijmeni
226	VladimĂ­r	LaĹˇtĹŻvka
5982	David	VodrĂˇĹľka
6154	Marek	Ĺ˝enĂ­Ĺˇek
6494	OndĹ™ej	VeselĂ˝
*/


-- 3. NaleznÄ›te poslance, kteĹ™Ă­ na ĹľĂˇdnĂ©m hlasovĂˇnĂ­ mimoĹ™ĂˇdnĂ© schĹŻze volebnĂ­ho obdobĂ­ 2013 - 2017 nehlasovali PROTI.
-- MimoĹ™ĂˇdnĂˇ schĹŻze se poznĂˇ tak, Ĺľe jejĂ­ schuze_stav.typ = 2.
-- HlasovĂˇnĂ­ PROTI mĂˇ hlasovani_poslanec.vysledek rovno 'B' nebo 'N'.
-- VypiĹˇte pouze poslance danĂ©ho volebnĂ­ho obdobĂ­. 
-- VypiĹˇte id_osoba, jmeno, prijmeni a setĹ™iÄŹte podle id_osoba.
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
                                   WHERE YEAR(organ.od_organ) = 2013
                                     AND schuze_stav.typ = 2
                                     AND hp.vysledek IN ('B', 'N'))
  AND poslanec.id_organ IN (SELECT organ.id_organ
                            FROM organ
                            WHERE YEAR(organ.od_organ) = 2013)

/*
id_osoba jmeno prijmeni
6152	Miloslav	BaÄŤiak
6245	Jan	Sobotka
6424	VĂˇclav	Valhoda
6425	Barbora	JelonkovĂˇ
*/

-- Varianta B

-------------
-- 1. Pro volebnĂ­ obdobĂ­ 2017-2021, naleznÄ›te osobu, kterĂˇ hlasovala nejÄŤastÄ›ji PROTI (hlasovani_poslanec.vysledek mĂˇ hodnoty "B" nebo "N")
-- v rĂˇmci poslancĹŻ ze stejnĂ© kandidĂˇtky (poslanec.id_kandidatka).
-- Tzn. v danĂ©m volebnĂ­m obdobĂ­ nenĂ­ osoba z danĂ© kandidĂˇtky, kterĂˇ by hlasovala vĂ­cekrĂˇt "B" nebo "N".
-- Do vĂ˝stupu uveÄŹte id_osoba, celĂ© jmĂ©no, pĹ™ijmenĂ­ osoby, id_kandidatka kde byla osoba zaĹ™azena a poÄŤet hlasovĂˇnĂ­ PROTI.
-- SetĹ™idte vĂ˝sledek podle id_kandidatka.
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


-----------------
-- 2.
-- VypiĹˇte osoby (id_osoba, jmeno, prijmeni), kterĂ© nÄ›kdy byly ve funkci pĹ™edsedy zemÄ›dÄ›lskĂ©ho vĂ˝boru, ale nikdy ve funkci mĂ­stropĹ™edsedy.
-- PĹ™edseda/mĂ­stopĹ™edseda zahraniÄŤnĂ­ho vĂ˝boru je funkce, kterĂˇ mĂˇ typ_funkce.typ_funkce_cz = 'PĹ™edseda'/'MĂ­stopĹ™edseda'
-- a orgĂˇn tĂ©to funkce mĂˇ organ.nazev_organu_cz = N'ZemÄ›dÄ›lskĂ˝ vĂ˝bor'.
SELECT osoba.id_osoba, jmeno, prijmeni
FROM osoba
WHERE osoba.id_osoba IN (SELECT z.id_osoba
                         FROM zarazeni z
                                  JOIN funkce f ON f.id_funkce = z.id_of AND z.cl_funkce = 1
                                  JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
                                  JOIN organ org ON f.id_organ = org.id_organ
                         WHERE tf.typ_funkce_cz = N'PĹ™edseda'
                           AND nazev_organu_cz = N'ZemÄ›dÄ›lskĂ˝ vĂ˝bor')
  AND osoba.id_osoba NOT IN (SELECT z.id_osoba
                             FROM zarazeni z
                                      JOIN funkce f ON f.id_funkce = z.id_of AND z.cl_funkce = 1
                                      JOIN typ_funkce tf ON f.id_typ_funkce = tf.id_typ_funkce
                                      JOIN organ org ON f.id_organ = org.id_organ
                             WHERE tf.typ_funkce_cz = N'MĂ­stopĹ™edseda'
                               AND nazev_organu_cz = N'ZemÄ›dÄ›lskĂ˝ vĂ˝bor')
/*
id_osoba jmeno prijmeni
164	Vlastimil	TlustĂ˝
228	Karel	Machovec
5944	Pavol	LukĹˇa
6216	Michal	KuÄŤera
*/


-- 3. NaleznÄ›te poslance, kteĹ™Ă­ na ĹľĂˇdnĂ©m hlasovĂˇnĂ­ mimoĹ™ĂˇdnĂ© schĹŻze volebnĂ­ho obdobĂ­ 2006 - 2010 nehlasovali PRO.
-- MimoĹ™ĂˇdnĂˇ schĹŻze se poznĂˇ tak, Ĺľe jejĂ­ schuze_stav.typ = 2.
-- HlasovĂˇnĂ­ PRO mĂˇ hlasovani_poslanec.vysledek rovno 'A'.
-- VypiĹˇte pouze poslance danĂ©ho volebnĂ­ho obdobĂ­. 
-- VypiĹˇte id_osoba, jmeno, prijmeni a setĹ™iÄŹte podle id_osoba.
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
                                   WHERE YEAR(organ.od_organ) = 2006
                                     AND schuze_stav.typ = 2
                                     AND hp.vysledek = 'A')
  AND poslanec.id_organ IN (SELECT organ.id_organ
                            FROM organ
                            WHERE YEAR(organ.od_organ) = 2006)

/*
id_osoba jmeno prijmeni
426	FrantiĹˇek	VnouÄŤek
5316	Jozef	Kubinyi
5888	KlĂˇra	SlĂˇmovĂˇ
5889	Yvona	KubjĂˇtovĂˇ
*/


----------------------------------------------------
----------------------------------------------------
-- ctvrtek 09:00 
-- Varianta A

-- 1
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

/*
zkratka, id_osoba, jmeno, prijmeni, hlasovaniPro
ANO	6246	Josef	Kott	5076
ÄŹĹĽËťSSD	5487	JiÄŹĹĽËťÄŹĹĽËť	PetrÄŹĹĽËť	5273
KDU-ÄŹĹĽËťSL	6170	Josef	UhlÄŹĹĽËťk	5356
KSÄŹĹĽËťM	5313	VladimÄŹĹĽËťr	KonÄŹĹĽËťÄŹĹĽËťek	5416
NezaÄŹĹĽËťaz	6195	Jana	HnykovÄŹĹĽËť	5160
ODS	5844	Jan	ZahradnÄŹĹĽËťk	5187
TOP09-S	5897	ZdenÄŹĹĽËťk	BezecnÄŹĹĽËť	5024
ÄŹĹĽËťsvit	6195	Jana	HnykovÄŹĹĽËť	5160
*/


----------
-- 2.
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
                                                    WHERE osoba.prijmeni = 'MaĹˇek'))  AS pocet_masek
           FROM schuze)
SELECT *
FROM T
WHERE T.pocet_okamura < T.pocet_masek


WITH T AS (SELECT id_schuze,
                  (SELECT COUNT(DISTINCT hlasovani.id_hlasovani)
                   FROM hlasovani
                            JOIN zmatecne_hlasovani_poslanec
                                 ON hlasovani.id_hlasovani = zmatecne_hlasovani_poslanec.id_hlasovani
                            JOIN osoba ON zmatecne_hlasovani_poslanec.id_osoba = osoba.id_osoba
                   WHERE hlasovani.schuze = schuze.schuze
                     AND hlasovani.id_organ = schuze.id_organ
                     AND osoba.prijmeni = 'Okamura') AS pocet_okamura,
                  (SELECT COUNT(DISTINCT hlasovani.id_hlasovani)
                   FROM hlasovani
                            JOIN zmatecne_hlasovani_poslanec
                                 ON hlasovani.id_hlasovani = zmatecne_hlasovani_poslanec.id_hlasovani
                            JOIN osoba ON zmatecne_hlasovani_poslanec.id_osoba = osoba.id_osoba
                   WHERE hlasovani.schuze = schuze.schuze
                     AND hlasovani.id_organ = schuze.id_organ
                     AND osoba.prijmeni = 'MaĹˇek')  AS pocet_masek
           FROM schuze)
SELECT *
FROM T
WHERE T.pocet_okamura < T.pocet_masek


/*
id_schuze, pocet_okamura, pocet_masek
710 0 1
*/


-- 3.SELECT poslanec.id_osoba, osoba.jmeno, osoba.prijmeni
    FROM
	poslanec
	JOIN osoba
ON poslanec.id_osoba = osoba.id_osoba
    JOIN organ ON poslanec.id_organ = organ.id_organ AND YEAR (organ.od_organ) = 2013
WHERE id_poslanec NOT IN (
    SELECT id_poslanec
    FROM hlasovani_poslanec
    JOIN hlasovani ON hlasovani_poslanec.id_hlasovani = hlasovani.id_hlasovani
    WHERE hlasovani_poslanec.vysledek = 'A'
  AND hlasovani.schuze = 2
    )
  AND id_poslanec IN (
    SELECT id_poslanec
    FROM hlasovani_poslanec
    JOIN hlasovani ON hlasovani_poslanec.id_hlasovani = hlasovani.id_hlasovani
    WHERE hlasovani.schuze = 2
    );

/*
id_osoba, jmeno, prijmeni
6138	Pavel	BÄŹĹĽËťlobrÄŹĹĽËťdek
6139	Josef	HÄŹĹĽËťjek
*/


-- Varianta B

-- 1.
WITH T AS
         (SELECT organ.zkratka, osoba.id_osoba, osoba.jmeno, osoba.prijmeni, COUNT(hp.id_hlasovani) AS hlasovaniProti
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
WHERE hlasovaniProti = (SELECT MAX(hlasovaniProti) FROM T t2 WHERE t1.zkratka = t2.zkratka)
ORDER BY t1.zkratka;

/*
zkratka, id_osoba, jmeno, prijmeni, hlasovaniProti
ďż˝SSD	5433	Jiďż˝ďż˝	Koskuba	1539
KSďż˝M	5948	Josef	Nekl	717
Nezaďż˝az	5952	Viktor	Paggio	1462
ODS	5895	Pavel	Bďż˝m	1616
TOP09-S	5908	Jaroslav	Eďż˝ek	1507
VV	5952	Viktor	Paggio	1462
*/


----------
-- 2. 
WITH T AS (SELECT id_schuze,
                  (SELECT COUNT(*)
                   FROM hlasovani
                   WHERE hlasovani.schuze = schuze.schuze
                     AND hlasovani.id_organ = schuze.id_organ
                     AND hlasovani.id_hlasovani IN (SELECT id_hlasovani
                                                    FROM zmatecne_hlasovani_poslanec
                                                             JOIN osoba ON zmatecne_hlasovani_poslanec.id_osoba = osoba.id_osoba
                                                    WHERE osoba.prijmeni = 'BabiĹˇ'))     AS pocet_babis,
                  (SELECT COUNT(*)
                   FROM hlasovani
                   WHERE hlasovani.schuze = schuze.schuze
                     AND hlasovani.id_organ = schuze.id_organ
                     AND hlasovani.id_hlasovani IN (SELECT id_hlasovani
                                                    FROM zmatecne_hlasovani_poslanec
                                                             JOIN osoba ON zmatecne_hlasovani_poslanec.id_osoba = osoba.id_osoba
                                                    WHERE osoba.prijmeni = 'HavlĂ­ÄŤek')) AS pocet_havlicek
           FROM schuze)
SELECT *
FROM T
WHERE T.pocet_babis < T.pocet_havlicek

/*
id_schuze, pocet_okamura, pocet_masek
710 0 1
*/


-- 3. 
SELECT poslanec.id_osoba, osoba.jmeno, osoba.prijmeni
FROM poslanec
         JOIN osoba ON poslanec.id_osoba = osoba.id_osoba
         JOIN organ ON poslanec.id_organ = organ.id_organ AND YEAR(organ.od_organ) = 2010
WHERE id_poslanec NOT IN (SELECT id_poslanec
                          FROM hlasovani_poslanec
                                   JOIN hlasovani ON hlasovani_poslanec.id_hlasovani = hlasovani.id_hlasovani
                          WHERE hlasovani_poslanec.vysledek = 'A'
                            AND hlasovani.schuze = 4)
  AND id_poslanec IN (SELECT id_poslanec
                      FROM hlasovani_poslanec
                               JOIN hlasovani ON hlasovani_poslanec.id_hlasovani = hlasovani.id_hlasovani
                      WHERE hlasovani.schuze = 4)
ORDER BY id_osoba

/*
id_osoba, jmeno, prijmeni
5974	Jiďż˝ďż˝	ďż˝lďż˝gr
5301	David	ďż˝eich
5342	Robin	Bďż˝hnisch
5768	Vojtďż˝ch	Adam
5297	Michal	Haďż˝ek
5270	Petr	Branďż˝
5272	Vďż˝clav	Votava
377	Miroslav	Kalousek
415	Pavel	Suchďż˝nek
5969	Zbynďż˝k	Stanjura
*/


----------------------------------------------------
----------------------------------------------------
-- PondÄ›lĂ­ 10:45

-- Varianta A

-- 1.
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

/*
id_osoba, jmeno, prijmeni, od_organ, do_organ, id_organ, pocetPRO
31	Vďż˝clav	Exner	2002-06-15	2006-06-15	168	7368
210	Milan	Ekert	2002-06-15	2006-06-15	168	7107
211	Milada	Emmerovďż˝	2002-06-15	2006-06-15	168	3925
5908	Jaroslav	Eďż˝ek	2010-05-29	2013-08-28	170	4051
6446	Frantiďż˝ek	Elfmark	2017-10-21	2021-10-20	172	5668
6747	Martin	Exner	2021-10-09	NULL	173	1835
*/


-- 2. 
SELECT id_osoba,
       jmeno,
       prijmeni,
       (SELECT COUNT(*)
        FROM zarazeni
                 JOIN funkce ON zarazeni.id_of = funkce.id_funkce AND zarazeni.cl_funkce = 1
        WHERE funkce.nazev_funkce_cz LIKE '%pďż˝edseda%'
          AND zarazeni.id_osoba = osoba.id_osoba) AS pocet_predseda,
       (SELECT COUNT(*)
        FROM zarazeni
                 JOIN organ ON zarazeni.id_of = organ.id_organ AND zarazeni.cl_funkce = 0
                 JOIN typ_organu ON organ.id_typ_org = typ_organu.id_typ_org
        WHERE typ_organu.nazev_typ_org_cz = 'Klub'
          AND zarazeni.id_osoba = osoba.id_osoba) AS pocet_klub
FROM osoba
WHERE YEAR(narozeni) > 1990;

/*
id_osoba, jmeno, prijmeni, pocet_predseda, pocet_klub
1871	Vďż˝clav	Jireďż˝ek	0	0
6449	Dominik	Feri	1	1
6456	Tereza	Hyďż˝hovďż˝	1	2
6499	Frantiďż˝ek	Kopďż˝iva	1	1
6623	Ondďż˝ej	Babka	2	2
6624	Frantiďż˝ek	Navrkal	1	1
6755	Jiďż˝ďż˝	Havrďż˝nek	1	1
6776	Klďż˝ra	Kocmanovďż˝	4	1
6788	Barbora	Urbanovďż˝	2	1
*/

-- 3.
SELECT osoba.id_osoba, osoba.jmeno, osoba.prijmeni
FROM osoba
WHERE id_osoba IN (SELECT id_osoba
                   FROM zarazeni
                            JOIN organ ON zarazeni.id_of = organ.id_organ AND zarazeni.cl_funkce = 0
                   WHERE organ.zkratka = 'ANO')
  AND id_osoba NOT IN (SELECT id_osoba
                       FROM zarazeni
                                JOIN funkce ON zarazeni.id_of = funkce.id_funkce AND zarazeni.cl_funkce = 1
                                JOIN typ_funkce ON funkce.id_typ_funkce = typ_funkce.id_typ_funkce
                       WHERE typ_funkce.typ_funkce_cz LIKE '%ministr%')
ORDER BY osoba.id_osoba

/*
119 vďż˝sledkďż˝
id_osoba, jmeno, prijmeni
5718	Jiďż˝ďż˝	Zlatuďż˝ka
6139	Josef	Hďż˝jek
6140	Martin	Komďż˝rek
6143	Stanislav	Berkovec
6144	Pavel	ďż˝rďż˝mek
6151	Miloďż˝	Babiďż˝
6152	Miloslav	Baďż˝iak
6153	Martin	Sedlďż˝ďż˝
6156	Kristďż˝na	Zelienkovďż˝
6158	Karel	Rais
...
*/


-- Varianta B

-- 1. 
WITH T AS
         (SELECT osoba.id_osoba,
                 osoba.jmeno,
                 osoba.prijmeni,
                 od_organ,
                 do_organ,
                 organ.id_organ,
                 COUNT(hlasovani_poslanec.id_poslanec) AS pocetPROTI
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
WHERE t1.pocetPROTI = (SELECT MAX(pocetPROTI) FROM T t2 WHERE t1.id_osoba = t2.id_osoba);

/*
id_osoba, jmeno, prijmeni, od_organ, do_organ, id_organ, pocetPROTI
422	Milan	Urban	2002-06-15	2006-06-15	168	1422
5275	Ladislav	Urban	2002-06-15	2006-06-15	168	2277
6170	Josef	Uhlďż˝k	2013-10-26	2017-10-26	171	1401
6788	Barbora	Urbanovďż˝	2021-10-09	NULL	173	1475
*/


-- 2. 
SELECT id_osoba,
       jmeno,
       prijmeni,
       (SELECT COUNT(*)
        FROM zarazeni
                 JOIN funkce ON zarazeni.id_of = funkce.id_funkce AND zarazeni.cl_funkce = 1
        WHERE funkce.nazev_funkce_cz LIKE '%vďż˝bor%'
          AND zarazeni.id_osoba = osoba.id_osoba) AS pocet_vybor,
       (SELECT COUNT(*)
        FROM zarazeni
                 JOIN organ ON zarazeni.id_of = organ.id_organ AND zarazeni.cl_funkce = 0
                 JOIN typ_organu ON organ.id_typ_org = typ_organu.id_typ_org
        WHERE typ_organu.nazev_typ_org_cz = 'klub'
          AND zarazeni.id_osoba = osoba.id_osoba) AS pocet_klub
FROM osoba
WHERE YEAR(narozeni) BETWEEN 1988 AND 1990;

/*
id_osoba, jmeno, prijmeni, pocet_vybor, pocet_klub
6475	Monika	Obornďż˝	0	2
6477	Jakub	Michďż˝lek	1	2
6489	Tomďż˝	Vymazal	0	1
6526	Ondďż˝ej	Profant	1	1
6742	Karel	Smetana	0	1
6750	Josef	Flek	1	1
6757	ďż˝imon	Heller	0	1
6834	Petr	Mikulica	0	0
*/

-- 3. 
SELECT osoba.id_osoba, osoba.jmeno, osoba.prijmeni
FROM osoba
WHERE id_osoba IN (SELECT id_osoba
                   FROM zarazeni
                            JOIN organ ON zarazeni.id_of = organ.id_organ AND zarazeni.cl_funkce = 0
                   WHERE organ.zkratka = 'ODS')
  AND id_osoba NOT IN (SELECT id_osoba
                       FROM zarazeni
                                JOIN funkce ON zarazeni.id_of = funkce.id_funkce AND zarazeni.cl_funkce = 1
                                JOIN typ_funkce ON funkce.id_typ_funkce = typ_funkce.id_typ_funkce
                       WHERE typ_funkce.typ_funkce_cz LIKE '%vedoucďż˝%')
ORDER BY osoba.id_osoba

/*
319 vďż˝sledkďż˝
id_osoba, jmeno, prijmeni
1	Petr	Bachna
2	Ivan	Beďż˝vďż˝ďż˝
3	Josef	Bejďż˝ek
4	Marek	Benda
7	Ladislav	Blaďż˝ek
10	Petr	Brodskďż˝
13	Vladimďż˝r	Budinskďż˝
15	Eduard	Bureďż˝
21	Petr	ďż˝ermďż˝k
22	Jan	ďż˝ernďż˝
...
*/


----------------------------------------------------
----------------------------------------------------
-- PondÄ›lĂ­ 14:15


-- A

-- 1. Pro vĹˇechny schĹŻze, kterĂ© zaÄŤaly v bĹ™eznu roku 2020 (year(schuze.od_schuze) = 2020 and month(schuze.od_schuze) = 3) 
-- naleznÄ›te osoby, kterĂ© nejÄŤastÄ›ji v hlasovĂˇnĂ­ch na danĂ© schĹŻzi hlasovali PRO (hlasovani_poslanec.vysledek = 'A').
-- VypiĹˇte id_osoba, jmeno, prijmeni, poĹ™adĂ­ schuze (hlasovani.schuze) a poÄŤet hlasĹŻ PRO osoby na danĂ© schĹŻzi.
WITH tabulka AS
         (SELECT o.id_osoba, o.jmeno, o.prijmeni, s.schuze, COUNT(*) AS hlasovani_pro
          FROM schuze s
                   JOIN hlasovani h ON h.id_organ = s.id_organ AND h.schuze = s.schuze
                   JOIN hlasovani_poslanec hp ON hp.id_hlasovani = h.id_hlasovani
                   JOIN poslanec p ON p.id_poslanec = hp.id_poslanec
                   JOIN osoba o ON p.id_osoba = o.id_osoba
          WHERE YEAR(s.od_schuze) = 2020
            AND MONTH(s.od_schuze) = 3
            AND hp.vysledek = 'A'
          GROUP BY o.id_osoba, o.jmeno, o.prijmeni, s.schuze)
SELECT t1.id_osoba, t1.jmeno, t1.prijmeni, t1.schuze, t1.hlasovani_pro
FROM tabulka t1
WHERE t1.hlasovani_pro >= ALL
      (SELECT t2.hlasovani_pro
       FROM tabulka t2
       WHERE t1.schuze = t2.schuze)

/*
id_osoba	jmeno	prijmeni	schuze	hlasovani_pro
6521	Radek	Rozvoral	41	84
6535	TomĂˇĹˇ	MartĂ­nek	42	77
*/

------------------------------------------------------------------------------------

-- 2. VypiĹˇte hlasovĂˇnĂ­ (id_hlasovani, schuze, cislo, bod, datum, cas, nazev_dlouhy) z volebnĂ­ho obdobĂ­ s id_organ = 172, 
-- kde osoba pĹ™Ă­jmenĂ­m BabiĹˇ hlasovala PRO (hlasovani_poslanec.vysledek='A') a osoba pĹ™Ă­jmenĂ­m StropnickĂ˝ hlasovala PROTI
-- (hlasovani_poslanec.vysledek je 'B' nebo 'N').
-- VĂ˝sledek bude setĹ™Ă­zen dle id_hlasovani.
SELECT h.id_hlasovani, h.schuze, h.cislo, h.bod, h.cas, h.nazev_dlouhy
FROM hlasovani h
WHERE h.id_organ = 172
  AND EXISTS
    (SELECT 1
     FROM hlasovani_poslanec hp
              JOIN poslanec p ON hp.id_poslanec = p.id_poslanec
              JOIN osoba o ON p.id_osoba = o.id_osoba
     WHERE o.prijmeni = 'BabiĹˇ'
       AND hp.vysledek = 'A'
       AND hp.id_hlasovani = h.id_hlasovani)
  AND EXISTS
    (SELECT 1
     FROM hlasovani_poslanec hp
              JOIN poslanec p ON hp.id_poslanec = p.id_poslanec
              JOIN osoba o ON p.id_osoba = o.id_osoba
     WHERE o.prijmeni = 'StropnickĂ˝'
       AND hp.vysledek IN ('B', 'N')
       AND hp.id_hlasovani = h.id_hlasovani)
ORDER BY h.id_hlasovani

/*
id_hlasovani	schuze	cislo	bod	datum	cas	nazev_dlouhy
67026	1	9	10	2017-11-22	17:23:00.0000000	NĂˇvrh na stanovenĂ­ poÄŤtu mĂ­stopĹ™edsedĹŻ PS
67250	4	131	6	2017-12-19	21:25:00.0000000	RozpoÄŤet SFDI na rok 2018
68038	17	5	1	2018-07-11	21:43:00.0000000	Â®Ăˇdost vlĂˇdy ÄŚeskĂ© republiky o vyslovenĂ­ dĹŻvÄ›ry
68039	17	6	1	2018-07-11	21:46:00.0000000	Â®Ăˇdost vlĂˇdy ÄŚeskĂ© republiky o vyslovenĂ­ dĹŻvÄ›ry
*/

------------------------------------------------------------------------------------

-- 3. VypiĹˇte nejmladĹˇĂ­ho poslance z kaĹľdĂ©ho kraje (poslanec.id_kraj), kteĹ™Ă­ se dostali do poslaneckĂ© snÄ›movny 
-- ve volebnĂ­m obdobĂ­ 2017 - 2021 (year(org.od_organ)=2017).
-- VypiĹˇte id_kraj, id_poslanec, id_osoba, jmĂ©no, pĹ™ijmenĂ­ a datum narozenĂ­.
-- VĂ˝sledek bude setĹ™Ă­zen dle id_kraj a id_poslanec.

SELECT p1.id_kraj, p1.id_poslanec, o1.id_osoba, o1.jmeno, o1.prijmeni, o1.narozeni
FROM poslanec p1
         JOIN osoba o1 ON p1.id_osoba = o1.id_osoba
         JOIN organ org1 ON p1.id_organ = org1.id_organ
WHERE YEAR(org1.od_organ) = 2017
  AND o1.narozeni >= ALL
      (SELECT o2.narozeni
       FROM poslanec p2
                JOIN osoba o2 ON p2.id_osoba = o2.id_osoba
       WHERE p1.id_kraj = p2.id_kraj
         AND p2.id_organ = org1.id_organ)
ORDER BY p1.id_kraj, p1.id_poslanec

/* VĂ˝sledek: 14 zĂˇznamĹŻ
id_kraj	id_poslanec	id_osoba	jmeno	prijmeni	narozeni
581	1564	6449	Dominik	Feri	1996-07-11
582	1609	6499	FrantiĹˇek	KopĹ™iva	1995-11-30
583	1733	6623	OndĹ™ej	Babka	1994-02-22
584	1610	6464	Barbora	KoĹ™anovĂˇ	1984-09-27
585	1695	6483	Petr	TĹ™eĹˇĹĂˇk	1983-01-04
586	1585	6456	Tereza	HyĹĄhovĂˇ	1995-02-23
587	1629	6535	TomĂˇĹˇ	MartĂ­nek	1986-01-23
588	1593	6462	Martin	JirĂˇnek	1978-04-10
589	1565	6450	MikulĂˇĹˇ	FerjenÄŤĂ­k	1987-03-19
590	1644	6475	Monika	ObornĂˇ	1989-04-02
591	1715	6489	TomĂˇĹˇ	Vymazal	1990-05-11
592	1656	6531	VojtÄ›ch	Pikal	1987-02-19
593	1728	6228	Marie	PÄ›nÄŤĂ­kovĂˇ	1979-12-31
594	1550	6442	LukĂˇĹˇ	ÄŚernohorskĂ˝	1984-11-19
*/


-- B

-- 1. Pro vĹˇechny schĹŻze, kterĂ© zaÄŤaly a skonÄŤily v dubnu roku 2021 (year(s.od_schuze)=2021 and month(s.od_schuze)=4 and month(s.do_schuze)=4) 
-- naleznÄ›te osoby, kterĂ© nejÄŤastÄ›ji v hlasovĂˇnĂ­ch na danĂ© schĹŻzi hlasovali PROTI (hlasovani_poslanec.vysledek je 'B' nebo 'N').
-- VypiĹˇte id_osoba, jmeno, prijmeni, poĹ™adĂ­ schuze (hlasovani.schuze) a poÄŤet hlasĹŻ PROTI osoby na danĂ© schĹŻzi.
-- VĂ˝sledek bude setĹ™Ă­zen dle poĹ™adĂ­ schĹŻze.
WITH tabulka AS
         (SELECT o.id_osoba, o.jmeno, o.prijmeni, s.schuze, COUNT(*) AS hlasovani_proti
          FROM schuze s
                   JOIN hlasovani h ON h.id_organ = s.id_organ AND h.schuze = s.schuze
                   JOIN hlasovani_poslanec hp ON hp.id_hlasovani = h.id_hlasovani
                   JOIN poslanec p ON p.id_poslanec = hp.id_poslanec
                   JOIN osoba o ON p.id_osoba = o.id_osoba
          WHERE YEAR(s.od_schuze) = 2021
            AND MONTH(s.od_schuze) = 4
            AND MONTH(s.do_schuze) = 4
            AND hp.vysledek IN ('B', 'N')
          GROUP BY o.id_osoba, o.jmeno, o.prijmeni, s.schuze)
SELECT t1.id_osoba, t1.jmeno, t1.prijmeni, t1.schuze, t1.hlasovani_proti
FROM tabulka t1
WHERE t1.hlasovani_proti >= ALL
      (SELECT t2.hlasovani_proti
       FROM tabulka t2
       WHERE t1.schuze = t2.schuze)
ORDER BY t1.schuze

/*
id_osoba	jmeno	prijmeni	schuze	hlasovani_proti
5847	Stanislav	JurĂˇnek	95	2
6496	Pavel	JuĹ™Ă­ÄŤek	96	2
6379	Miloslava	RutovĂˇ	97	9
5911	Jaroslav	Foldyna	100	10
*/

------------------------------------------------------------------------------------

-- 2. VypiĹˇte hlasovĂˇnĂ­ (id_hlasovani, schuze, cislo, bod, datum, cas, nazev_dlouhy) z roku 2017 (year(datum)=2017), 
-- kde osoba pĹ™Ă­jmenĂ­m BabiĹˇ hlasovala PRO (hlasovani_poslanec.vysledek='A') a osoba pĹ™Ă­jmenĂ­m DostĂˇlovĂˇ hlasovala PROTI
-- (hlasovani_poslanec.vysledek je 'B' nebo 'N').
-- VĂ˝sledek bude setĹ™Ă­zen dle id_hlasovani.

SELECT h.id_hlasovani, h.schuze, h.cislo, h.bod, h.cas, h.nazev_dlouhy
FROM hlasovani h
WHERE YEAR(h.datum) = 2017
  AND EXISTS
    (SELECT 1
     FROM hlasovani_poslanec hp
              JOIN poslanec p ON hp.id_poslanec = p.id_poslanec
              JOIN osoba o ON p.id_osoba = o.id_osoba
     WHERE o.prijmeni = 'BabiĹˇ'
       AND hp.vysledek = 'A'
       AND hp.id_hlasovani = h.id_hlasovani)
  AND EXISTS
    (SELECT 1
     FROM hlasovani_poslanec hp
              JOIN poslanec p ON hp.id_poslanec = p.id_poslanec
              JOIN osoba o ON p.id_osoba = o.id_osoba
     WHERE o.prijmeni = 'DostĂˇlovĂˇ'
       AND hp.vysledek IN ('B', 'N')
       AND hp.id_hlasovani = h.id_hlasovani)
ORDER BY h.id_hlasovani

/*
id_hlasovani	schuze	cislo	bod	cas	nazev_dlouhy
67026	1	9	10	17:23:00.0000000	NĂˇvrh na stanovenĂ­ poÄŤtu mĂ­stopĹ™edsedĹŻ PS
67250	4	131	6	21:25:00.0000000	RozpoÄŤet SFDI na rok 2018
*/

------------------------------------------------------------------------------------

-- 3. VypiĹˇte nejstarĹˇĂ­ho poslance z kaĹľdĂ©ho kraje (poslanec.id_kraj), kteĹ™Ă­ se dostali do poslaneckĂ© snÄ›movny 
-- ve volebnĂ­m obdobĂ­ 2013 - 2017 (year(org.od_organ)=2013).
-- VypiĹˇte id_kraj, id_poslanec, id_osoba, jmĂ©no, pĹ™ijmenĂ­ a poÄŤet rokĹŻ poslance 1. den snÄ›movny 
-- (pro vĂ˝poÄŤet pouĹľijte atributy organ.od_organ a osoba.narozeni).
-- VĂ˝sledek bude setĹ™Ă­zen dle id_kraj a id_poslanec.

SELECT p1.id_kraj,
       p1.id_poslanec,
       o1.id_osoba,
       o1.jmeno,
       o1.prijmeni,
       DATEDIFF(YEAR, o1.narozeni, org1.od_organ) AS pocet_roku
FROM poslanec p1
         JOIN osoba o1 ON p1.id_osoba = o1.id_osoba
         JOIN organ org1 ON p1.id_organ = org1.id_organ
WHERE YEAR(org1.od_organ) = 2013
  AND o1.narozeni <= ALL
      (SELECT o2.narozeni
       FROM poslanec p2
                JOIN osoba o2 ON p2.id_osoba = o2.id_osoba
       WHERE p1.id_kraj = p2.id_kraj
         AND p2.id_organ = org1.id_organ)
ORDER BY p1.id_kraj, p1.id_poslanec

/* VĂ˝sledek: 14 zĂˇznamĹŻ
id_kraj	id_poslanec	id_osoba	jmeno	prijmeni	pocet_roku
581	1458	5558	Karel	Schwarzenberg	76
582	1489	6164	Josef	VondrĂˇĹˇek	63
583	1448	6234	Karel	PraĹľĂˇk	68
584	1413	392	Jaroslav	Lobkowicz	71
585	1333	6183	Jaroslav	Borka	61
586	1325	6136	Marie	BeneĹˇovĂˇ	65
587	1371	5919	VĂˇclav	HorĂˇÄŤek	57
588	1474	5975	JiĹ™Ă­	Ĺ tÄ›tina	72
589	1311	6148	Augustin Karel	Andrle Sylor	67
590	1320	6002	JiĹ™Ă­	BÄ›hounek	61
591	1356	305	Miroslav	GrebenĂ­ÄŤek	66
592	1338	5307	Alexander	ÄŚernĂ˝	60
593	1486	6167	Pavel	VolÄŤĂ­k	63
594	1414	6219	Jana	LorencovĂˇ	73
*/