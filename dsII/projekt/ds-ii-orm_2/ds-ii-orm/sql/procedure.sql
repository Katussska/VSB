CREATE OR ALTER PROCEDURE createNewAlbum @name NVARCHAR(50),
                                         @description NVARCHAR(200),
                                         @releaseDate DATE,
                                         @artistList VARCHAR(MAX), -- Seznam umělců
                                         @songList VARCHAR(MAX) -- Seznam písní
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @artists TABLE
                     (
                         artist_id INT
                     );
    INSERT INTO @artists (artist_id)
    SELECT value
    FROM STRING_SPLIT(@artistList, ',');

    DECLARE @songs TABLE
                   (
                       song_id INT
                   );
    INSERT INTO @songs (song_id)
    SELECT value
    FROM STRING_SPLIT(@songList, ',');

    DECLARE @albumId INT;

-- Funkce zjisti, zda zadany nazev alba jiz neobsahuje jine umelcovo album
    IF EXISTS (SELECT 1
               FROM album al
                        JOIN album_artist aa ON al.album_id = aa.album_id
                        JOIN artist ar ON aa.artist_id = ar.artist_id
               WHERE al.name = @name
                 AND ar.artist_id IN (SELECT artist_id FROM @artists))
        BEGIN
            RAISERROR ('Album name already exists for one of the artists.', 16, 1);
            RETURN;
        END;

-- Funkce zjisti, zda-li dany song se nenachazi jiz v jinem albu nektereho z umelcu
    IF EXISTS (SELECT 1
               FROM artist ar
                        JOIN album_artist aa ON ar.artist_id = aa.artist_id
                        JOIN album al ON aa.album_id = al.album_id
                        JOIN song s ON al.album_id = s.album_id
               WHERE ar.artist_id IN (SELECT artist_id FROM @artists)
                 AND s.song_id IN (SELECT song_id FROM @songs))
        BEGIN
            RAISERROR ('One or more songs are already present in another album by one of the artists.', 16, 1);
            RETURN;
        END;


    BEGIN TRANSACTION;

-- Vložení nového alba
    INSERT INTO album (release_date, name, description)
    VALUES (@releaseDate, @name, @description);
    SET @albumId = SCOPE_IDENTITY();

-- Přiřazení alba k umělcům
    INSERT INTO album_artist (album_id, artist_id)
    SELECT @albumId, artist_id
    FROM @artists;

-- Přiřazení písní k albu
    UPDATE song
    SET album_id = @albumId
    WHERE song_id IN (SELECT song_id FROM @songs);

-- Přiřazení vazeb ke všem umělcům ke všem písním v albu
    INSERT INTO song_artist (song_id, artist_id)
    SELECT s.song_id, aa.artist_id
    FROM song s
             JOIN @songs ss ON s.song_id = ss.song_id
             JOIN album_artist aa ON s.album_id = aa.album_id
    WHERE s.album_id = @albumId;

    COMMIT TRANSACTION;
END;


-- DECLARE @name NVARCHAR(50) = 'Testovaci album';
-- DECLARE @description NVARCHAR(200) = 'Popis testovaciho alba.';
-- DECLARE @releaseDate DATE = '2024-05-16';
-- DECLARE @artistList VARCHAR(MAX) = '1,2,3'; -- Seznam ID umělců oddělených čárkami
-- DECLARE @songList VARCHAR(MAX) = '10,9,8'; -- Seznam ID písní oddělených čárkami
--
--     EXEC createNewAlbum
--          @name = @name,
--          @description = @description,
--          @releaseDate = @releaseDate,
--          @artistList = @artistList,
--          @songList = @songList;
