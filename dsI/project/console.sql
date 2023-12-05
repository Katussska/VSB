--1;1;200;Seznam alb seřazený podle data vydání vzestupně
SELECT *
FROM Album
ORDER BY release_date;

--1;2;1999;Seznam skladeb seřazený podle délky od nejkratší po nejdelší
SELECT name, duration
FROM Song
ORDER BY duration;

--1;3;1000;Seznam uživatelů a jejich jmen, seřazený podle username
SELECT username, name
FROM [User]
ORDER BY username DESC;

--1;4;44;Seznam umělců a počet skladeb, které každý umělec vytvořil, seřazený podle počtu skladeb vzestupně
SELECT artist.name, COUNT(song_artist.song_id) AS počet_skladeb
FROM artist
         LEFT JOIN song_artist ON artist.artist_id = song_artist.artist_id
GROUP BY artist.name
ORDER BY počet_skladeb;
