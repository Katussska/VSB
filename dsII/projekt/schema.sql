CREATE TABLE [user]
(
    user_id           INT PRIMARY KEY NOT NULL IDENTITY (1,1),
    registration_date DATE            NOT NULL,
    premium_status    BIT             NOT NULL,
    username          VARCHAR(50)     NOT NULL,
    password          varchar(50)     NOT NULL,
    email             VARCHAR(50)     NOT NULL,
    name              VARCHAR(50)
);

CREATE TABLE [artist]
(
    artist_id INT PRIMARY KEY NOT NULL IDENTITY (1,1),
    user_id   INT             NOT NULL,
    biography VARCHAR(MAX)    NOT NULL,
    name      VARCHAR(50)     NOT NULL,
    country   VARCHAR(50)
);

ALTER TABLE [artist]
    ADD CONSTRAINT [artist_user_id_foreign]
        FOREIGN KEY
            ([user_id]) REFERENCES [user] ([user_id]);

CREATE TABLE [album]
(
    album_id     INT PRIMARY KEY NOT NULL IDENTITY (1,1),
    release_date DATE            NOT NULL,
    name         VARCHAR(50)     NOT NULL,
    description  VARCHAR(200)
);

CREATE TABLE [song]
(
    song_id      INT PRIMARY KEY NOT NULL IDENTITY (1,1),
    release_date DATE            NOT NULL,
    duration     VARCHAR(50)     NOT NULL,
    name         VARCHAR(100)    NOT NULL,
    album_id     INT,
    lyrics       VARCHAR(MAX)
);

ALTER TABLE [song]
    ADD CONSTRAINT [song_album_id_foreign]
        FOREIGN KEY
            ([album_id]) REFERENCES [album] ([album_id])

CREATE TABLE [album_artist]
(
    album_id   INT NOT NULL,
    artist_id INT NOT NULL
);

ALTER TABLE [album_artist]
    ADD CONSTRAINT [album_artist_album_id_primary_foreign]
        FOREIGN KEY
            ([album_id]) REFERENCES [album] ([album_id])

ALTER TABLE [album_artist]
    ADD CONSTRAINT [album_artist_artist_id_primary_foreign]
        FOREIGN KEY
            ([artist_id]) REFERENCES [artist] ([artist_id])

CREATE TABLE [song_artist]
(
    song_id   INT NOT NULL,
    artist_id INT NOT NULL
);

ALTER TABLE [song_artist]
    ADD CONSTRAINT [song_artist_song_id_primary_foreign]
        FOREIGN KEY
            ([song_id]) REFERENCES [song] ([song_id])

ALTER TABLE [song_artist]
    ADD CONSTRAINT [song_artist_artist_id_primary_foreign]
        FOREIGN KEY
            ([artist_id]) REFERENCES [artist] ([artist_id]);