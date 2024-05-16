package dev.katussska.dao;

import dev.katussska.Database;
import dev.katussska.dto.Album;
import dev.katussska.dto.Artist;
import dev.katussska.dto.Song;

import java.sql.*;
import java.util.List;

public class AlbumDao {
    /**
     *
     * @param pDb
     * @param album
     * @return inserted album id
     * @throws SQLException
     */
    private static int insert(Database pDb, Album album) throws SQLException {
        Database db = Database.connect(pDb);
        String sql = """
            INSERT INTO album(name, release_date, description)
            VALUES (?, ?, ?)
            """;
        try (PreparedStatement statement = db.getConn().prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS)) {
            statement.setString(1, album.getName());
            statement.setDate(2, album.getReleaseDate());
            statement.setString(3, album.getDescription());
            int affectedRows = statement.executeUpdate();

            if (affectedRows == 0) {
                throw new SQLException("Creating album failed, no rows affected.");
            }
            try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    Database.close(pDb, db);
                    return generatedKeys.getInt(1);
                } else {
                    throw new SQLException("Creating album failed, no ID obtained.");
                }
            }
        }
    }

    public static void createNewAlbum(Database pDb, String name, String description, Date releaseDate, List<Artist> artists, List<Song> songs) throws SQLException {
        Database db = Database.connect(pDb);

        for (Artist artist : artists) {
            if (ArtistDao.albumNameExists(db, artist, name))
                throw new SQLException("Album name already exists");

            for (Song song : songs) {
                if (ArtistDao.isSongInAlbumAlready(db, artist, song))
                    throw new SQLException("Song is already in an album by one of the artists");
            }
        }

        try {
            db.beginTransaction();

            Album album = new Album(releaseDate, name, description);
            Integer albumId = AlbumDao.insert(db, album);

            for (Artist artist : artists) {
                AlbumArtistDao.insert(db, albumId, artist);
            }

            for (Song song : songs) {
                SongDao.insert(db, song);
                for (Artist artist : artists) {
                    SongArtistDao.insert(db, song, artist);
                }
            }

            db.endTransaction();
        } catch (SQLException e) {
            db.rollback();
        }

        Database.close(pDb, db);
    }
}
