/*1;1;200;Seznam alb seřazený podle data vydání vzestupně*/
SELECT *
FROM Album
ORDER BY release_date;

/*1;2;420;Seznam skladeb s délkou větší než 12 min seřazený podle délky od nejkratší po nejdelší*/
SELECT name, duration
FROM Song
GROUP BY name, duration
HAVING MAX(song.duration) > '0:12:00'
ORDER BY duration;


/*1;3;500;Seznam uživatelů a jejich jmen, seřazený podle username*/
SELECT username, name
FROM [User]
ORDER BY username DESC;

/*1;4;44;Seznam umělců a počet skladeb, které každý umělec vytvořil, seřazený podle počtu skladeb vzestupně*/
SELECT artist.name, COUNT(song_artist.song_id) AS počet_skladeb
FROM artist
         LEFT JOIN song_artist ON artist.artist_id = song_artist.artist_id
GROUP BY artist.name
ORDER BY počet_skladeb;

/*2;1;11;Seznam alb, která byla vydána po roce 2022 a mají jméno začínající na S*/
SELECT album.name, album_id
FROM Album
WHERE release_date > '2022-01-01'
  AND name LIKE 'S%';

/*2;2;287;Seznam skladeb, které patří do alba s id 5 nebo byly vydány po roce 2023*/
SELECT song.name
FROM Song
WHERE album_id = 5
   OR release_date > '2023-01-01';

/*2;3;233;Seznam uživatelů, kteří nemají premium status*/
SELECT user_id, username
FROM [User]
WHERE premium_status != 1;

/*2;4;7;Seznam umělců, jejichž jméno začíná na 'B' nebo 'C' a vydali více jak 50 skladeb*/
SELECT artist.name, artist.country, COUNT(song_artist.song_id) AS počet_skladeb
FROM Artist
         LEFT JOIN song_artist ON Artist.artist_id = song_artist.artist_id
WHERE NOT artist.country = 'China' AND name LIKE 'B%'
   OR name LIKE 'C%'
GROUP BY artist.name, artist.country
HAVING COUNT(song_artist.song_id) > 50;

/*3;1;8;Alba, která mají alespoň 15 skladeb pomocí IN*/
SELECT album_id, name
FROM Album
WHERE album_id IN (SELECT album_id
                   FROM Song
                   GROUP BY album_id
                   HAVING COUNT(song_id) >= 15);

/*3;2;8;Alba, která mají alespoň 15 skladeb pomocí EXIST*/
SELECT album_id, name
FROM Album A
WHERE EXISTS (SELECT 1
              FROM Song S
              WHERE S.album_id = A.album_id
              GROUP BY S.album_id
              HAVING COUNT(S.song_id) >= 15);

/*3;3;8;Alba, která mají alespoň 15 skladeb pomocí ALL*/
SELECT album_id, name
FROM Album A
WHERE 15 <= ALL (SELECT COUNT(song_id)
                 FROM Song S
                 WHERE S.album_id = A.album_id
                 GROUP BY album_id);


/*3;4;8;Alba, která mají alespoň 15 skladeb pomocí INTERSECT*/
SELECT album_id, name
FROM Album
INTERSECT
SELECT Album.album_id, album.name
FROM Album
         JOIN Song ON Album.album_id = Song.album_id
GROUP BY Album.album_id, artist_id, album.release_date, album.name
HAVING COUNT(Song.song_id) >= 15;

/*4;1;8;Alba s maximální délkou skladby větší než 1 min a menší než 10 min s použitím GROUP BY*/
SELECT Album.name, MAX(Song.duration) AS průměrná_délka
FROM Album
         LEFT JOIN Song ON Album.album_id = Song.album_id
GROUP BY Album.name
HAVING MAX(song.duration) > '0:01:00'
   AND MAX(song.duration) < '0:10:00'

/*4;2;42;Seznam umělců a s počtem alb > 16 s použitím GROUP BY a HAVING*/
SELECT artist.name, COUNT(album_id) AS počet_alb
FROM Album
         JOIN artist ON Album.artist_id = artist.artist_id
GROUP BY artist.name
HAVING COUNT(album_id) > 1

/*4;3;77;Skladby s průběrným hodnocením 1*/
SELECT Song.name, AVG(rating_value) AS průměrné_hodnocení
FROM Song
         LEFT JOIN Rating ON Song.song_id = Rating.song_id
GROUP BY Song.name
HAVING AVG(rating_value) = 1;

/*4;4;50;Maximální délka skladeb v albech umělců*/
SELECT Artist.artist_id, Artist.name, MAX(Song.duration) AS maximální_délka_skladeb
FROM Artist
         LEFT JOIN Album ON Artist.artist_id = Album.artist_id
         LEFT JOIN Song ON Album.album_id = Song.album_id
GROUP BY Artist.artist_id, Artist.name;

/*5;1;200;ID alb a počet skladeb v nich pomocí JOIN*/
SELECT A.album_id, COUNT(S.song_id) AS počet_skladeb
FROM Album A
         JOIN Song S ON A.album_id = S.album_id
GROUP BY A.album_id;

/*5;2;200;ID alb a počet skladeb v nich pomocí IN*/
SELECT A.album_id,
       (SELECT COUNT(song_id)
        FROM Song
        WHERE album_id = A.album_id) AS počet_skladeb
FROM Album A
WHERE A.album_id IN (SELECT album_id
                     FROM Song)
GROUP BY A.album_id;

/*5;3;995;Seznam playlistu s počtem jejich skladeb*/
SELECT SP.playlist_id, playlist.name, COUNT(SP.song_id) AS počet_skladeb_v_playlistu
FROM song_playlist SP
         LEFT JOIN playlist ON SP.playlist_id = playlist.playlist_id
GROUP BY SP.playlist_id, playlist.name;


/*5;4;87;Seznam alb s počtem skladeb, které mají skladby s id větší než 1800 a obsahují text s použitím GROUP BY a WHERE*/
SELECT A.album_id, COUNT(S.song_id) AS počet_skladeb
FROM Album A
         LEFT JOIN Song S ON A.album_id = S.album_id
WHERE S.song_id > 1800
  AND s.lyrics IS NOT NULL
GROUP BY A.album_id;

/*6;1;4;Seznam písní s nadprůměrným počtem hodnocení*/
SELECT s.song_id,
       s.name,
       (SELECT COUNT(r.rating_id)
        FROM Rating r
        WHERE r.song_id = s.song_id) AS rating_count
FROM Song s
         JOIN (SELECT sp.song_id, p.playlist_id
               FROM Song_playlist sp
                        JOIN Playlist p ON sp.playlist_id = p.playlist_id) AS song_Playlist
              ON s.song_id = song_Playlist.song_id
WHERE (SELECT COUNT(r.rating_id)
       FROM Rating r
       WHERE r.song_id = s.song_id) > (SELECT AVG(rating_count)
                                       FROM (SELECT COUNT(r.rating_id) AS rating_count
                                             FROM Song s
                                                      JOIN Song_playlist sp ON s.song_id = sp.song_id
                                                      JOIN Rating r ON s.song_id = r.song_id
                                             GROUP BY s.song_id, s.name) AS subquery)
GROUP BY s.song_id, s.name

/*6;2;59;Výběr skladby s nejvyšším hodnocením a jejím umělcem, jehož jméno musí začínat na
  B a musí mít uvedenou zemi původu*/
SELECT S.song_id, S.name, A.name, R.rating_value AS nejvyšší_hodnocení
FROM Song S
         JOIN SONG_ARTIST SA ON S.song_id = SA.song_id
         JOIN Artist A ON SA.artist_id = A.artist_id
         JOIN (SELECT song_id, MAX(rating_value) AS rating_value
               FROM Rating
               GROUP BY song_id) R ON S.song_id = R.song_id
WHERE A.name LIKE 'B%'
  AND A.country IS NOT NULL;