-- Vytvoření uživatelů
INSERT INTO [user] (registration_date, premium_status, username, password, email, name)
VALUES ('2022-01-01', 0, 'user1', 'password1', 'user1@email.com', 'User One'),
       ('2022-02-01', 0, 'user2', 'password2', 'user2@email.com', 'User Two'),
       ('2022-03-01', 0, 'user3', 'password3', 'user3@email.com', 'User Three');

-- Vytvoření umělců
INSERT INTO [artist] (user_id, biography, name, country)
VALUES ((SELECT user_id FROM [user] WHERE username = 'user1'), 'Biography 1', 'Artist One', 'Country One'),
    ((SELECT user_id FROM [user] WHERE username = 'user2'), 'Biography 2', 'Artist Two', 'Country Two'),
    ((SELECT user_id FROM [user] WHERE username = 'user3'), 'Biography 3', 'Artist Three', 'Country Three');

-- Vytvoření alb
INSERT INTO [album] (release_date, name, description)
VALUES ('2022-04-01', 'Album One', 'This is the first album'),
       ('2022-05-01', 'Album Two', 'This is the second album');

-- Přiřazení alb umělcům
INSERT INTO [album_artist] (album_id, artist_id)
VALUES ((SELECT album_id FROM [album] WHERE name = 'Album One'),
       (SELECT artist_id FROM [artist] WHERE name = 'Artist One')),
       ((SELECT album_id FROM [album] WHERE name = 'Album Two'),
        (SELECT artist_id FROM [artist] WHERE name = 'Artist Two')),
       ((SELECT album_id FROM [album] WHERE name = 'Album Two'),
        (SELECT artist_id FROM [artist] WHERE name = 'Artist Three'));

-- Vytvoření písní a přiřazení k umělcům
INSERT INTO [song] (release_date, duration, name, album_id, lyrics)
VALUES ('2022-06-02', '1', 'Song 1', (SELECT album_id FROM [album] WHERE name = 'Album One'), 'Lyrics for song 1'),
    ('2022-06-03', '2', 'Song 2', (SELECT album_id FROM [album] WHERE name = 'Album One'), 'Lyrics for song 2'),
    ('2022-06-04', '3', 'Song 3', (SELECT album_id FROM [album] WHERE name = 'Album Two'), 'Lyrics for song 3'),
    ('2022-06-05', '4', 'Song 4', (SELECT album_id FROM [album] WHERE name = 'Album Two'), 'Lyrics for song 4'),
    ('2022-06-06', '5', 'Song 5', (SELECT album_id FROM [album] WHERE name = 'Album Two'), 'Lyrics for song 5'),
    ('2022-06-07', '6', 'Song 6', NULL, 'Lyrics for song 6'),
    ('2022-06-08', '7', 'Song 7', NULL, 'Lyrics for song 7'),
    ('2022-06-09', '8', 'Song 8', NULL, 'Lyrics for song 8'),
    ('2022-06-10', '9', 'Song 9', NULL, 'Lyrics for song 9'),
    ('2022-06-11', '10', 'Song 10', NULL, 'Lyrics for song 10');

-- Přiřazení písní umělcům
INSERT INTO [song_artist] (song_id, artist_id)
SELECT s.song_id, a.artist_id
FROM [song] s
    JOIN [album] al ON s.album_id = al.album_id
    JOIN [album_artist] a ON al.album_id = a.album_id
WHERE s.album_id IS NOT NULL;
