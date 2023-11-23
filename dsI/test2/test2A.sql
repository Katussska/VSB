CREATE TABLE Volebniobdobi
(
    id_obdobi INT IDENTITY,
    zacatek   DATE NOT NULL,
    konec     DATE DEFAULT NULL,
    PRIMARY KEY (id_obdobi)
)

ALTER TABLE Volebniobdobi
    ADD PRIMARY KEY (id_obdobi)

INSERT INTO Volebniobdobi(zacatek, konec)
SELECT organ.od_organ AS zacatek, organ.do_organ AS konec
FROM organ
WHERE organ.id_organ BETWEEN 165 AND 173

SELECT *
FROM Volebniobdobi

ALTER TABLE omluva
    DROP CONSTRAINT omluvy_fk_id_organ

UPDATE omluva
SET id_organ = (SELECT id_obdobi
                FROM Volebniobdobi
                         JOIN organ o ON o.id_organ = omluva.id_organ
                WHERE o.od_organ = Volebniobdobi.zacatek)


ALTER TABLE omluva
    ADD CONSTRAINT fk_organ_obdobi FOREIGN KEY (id_organ) REFERENCES Volebniobdobi (id_obdobi)


CREATE TABLE VolebniObdobi
(
    id_obdobi int IDENTITY PRIMARY KEY NOT NULL,
    zacatek   date                     NOT NULL,
    konec     date                     NULL DEFAULT NULL,
)

SELECT *
FROM VolebniObdobi
SELECT *
FROM poslanec

--2
INSERT INTO VolebniObdobi
SELECT od_organ, do_organ
FROM organ
WHERE id_organ >= 165
  AND id_organ <= 173

--3
ALTER TABLE poslanec
    DROP CONSTRAINT poslanec_fk_id_obdobi

--4
UPDATE poslanec
SET id_organ =
        (SELECT id_obdobi
         FROM VolebniObdobi
                  JOIN organ org ON org.od_organ = VolebniObdobi.zacatek
                  JOIN poslanec p ON p.id_organ = org.id_organ
         WHERE p.id_poslanec = poslanec.id_poslanec)

--5
ALTER TABLE poslanec
    ADD CONSTRAINT fk_poslanec_id_org FOREIGN KEY (id_organ)
        REFERENCES VolebniObdobi (id_obdobi)

SELECT *
FROM poslanec
         JOIN VolebniObdobi ON VolebniObdobi.id_obdobi = poslanec.id_organ
SELECT *
FROM VolebniObdobi