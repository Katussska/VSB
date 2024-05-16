CREATE OR ALTER PROCEDURE createNewAlbum @name NVARCHAR(50),
                                         @description NVARCHAR(200),
                                         @releaseDate DATE,
                                         @artistList VARCHAR(MAX),
                                         @songList VARCHAR(MAX)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        -- SQL temp tables store data temporarily during query or procedure execution,
        -- existing only within the session and auto-dropping at session end,
        -- facilitating data storage and manipulation sans permanent table creation.
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

        -- Check if album name already exists for one of the artists.
        IF EXISTS (SELECT 1
                   FROM album al
                            JOIN album_artist aa ON al.album_id = aa.album_id
                            JOIN artist ar ON aa.artist_id = ar.artist_id
                   WHERE al.name = @name
                     AND ar.artist_id IN (SELECT artist_id FROM @artists))
            BEGIN
                -- 16 indicates the severity level of the error, and the number 1 is the state value.
                RAISERROR ('Album name already exists for one of the artists.', 16, 1);
                RETURN;
            END;

        -- Check if any song is already present in another album by one of the artists
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

        -- Insert new album.
        INSERT INTO album (release_date, name, description)
        VALUES (@releaseDate, @name, @description);
        SET @albumId = SCOPE_IDENTITY();

        -- Assign album to artists.
        INSERT INTO album_artist (album_id, artist_id)
        SELECT @albumId, artist_id
        FROM @artists;

        -- Assign songs to album.
        UPDATE song
        SET album_id = @albumId
        WHERE song_id IN (SELECT song_id FROM @songs);

        -- Assign all artists to all songs in the album.
        INSERT INTO song_artist (song_id, artist_id)
        SELECT s.song_id, aa.artist_id
        FROM song s
                 JOIN @songs ss ON s.song_id = ss.song_id
                 JOIN album_artist aa ON s.album_id = aa.album_id
        WHERE s.album_id = @albumId;

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        -- If an error occurred, rollback the transaction.
        ROLLBACK TRANSACTION;
        -- Re-throw the error.
        THROW;
    END CATCH;
END;

-- Trouble-free creation of the album (many songs and artists).
DECLARE @name NVARCHAR(50) = 'Test album 1';
DECLARE @description NVARCHAR(200) = 'Popis testovaciho alba 1.';
DECLARE @releaseDate DATE = '2024-05-16';
DECLARE @artistList VARCHAR(MAX) = '1,2,3';
DECLARE @songList VARCHAR(MAX) = '8,9,10';

    EXEC createNewAlbum
         @name = @name,
         @description = @description,
         @releaseDate = @releaseDate,
         @artistList = @artistList,
         @songList = @songList;

-- Album name already exists.
DECLARE @name NVARCHAR(50) = 'Test album 1';
DECLARE @description NVARCHAR(200) = 'Popis testovaciho alba 2.';
DECLARE @releaseDate DATE = '2024-05-16';
DECLARE @artistList VARCHAR(MAX) = '1,3';
DECLARE @songList VARCHAR(MAX) = '6';

    EXEC createNewAlbum
         @name = @name,
         @description = @description,
         @releaseDate = @releaseDate,
         @artistList = @artistList,
         @songList = @songList;

-- One or more songs are already present in another album.
DECLARE @name NVARCHAR(50) = 'Test album 3';
DECLARE @description NVARCHAR(200) = 'Popis testovaciho alba 3.';
DECLARE @releaseDate DATE = '2024-05-16';
DECLARE @artistList VARCHAR(MAX) = '2';
DECLARE @songList VARCHAR(MAX) = '10';

    EXEC createNewAlbum
         @name = @name,
         @description = @description,
         @releaseDate = @releaseDate,
         @artistList = @artistList,
         @songList = @songList;

-- Trouble-free creation of the album (one song and artist).
DECLARE @name NVARCHAR(50) = 'Test album 4';
DECLARE @description NVARCHAR(200) = 'Popis testovaciho alba 4.';
DECLARE @releaseDate DATE = '2024-05-16';
DECLARE @artistList VARCHAR(MAX) = '2';
DECLARE @songList VARCHAR(MAX) = '7';

    EXEC createNewAlbum
         @name = @name,
         @description = @description,
         @releaseDate = @releaseDate,
         @artistList = @artistList,
         @songList = @songList;