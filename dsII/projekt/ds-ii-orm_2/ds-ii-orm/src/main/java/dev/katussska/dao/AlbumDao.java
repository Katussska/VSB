package dev.katussska.dao;

import dev.katussska.dto.Album;
import dev.katussska.dto.Artist;
import dev.katussska.dto.Song;

import java.sql.*;
import java.util.List;

public class AlbumDao {
    /**
     * @param pDb
     * @param album
     * @return inserted album id
     * @throws SQLException
     */
    private static int insert(Connection db, Album album) throws SQLException {
        String sql = """
                INSERT INTO album(name, release_date, description)
                VALUES (?, ?, ?)
                """;
        try (PreparedStatement statement = db.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS)) {
            statement.setString(1, album.getName());
            statement.setDate(2, album.getReleaseDate());
            statement.setString(3, album.getDescription());
            int affectedRows = statement.executeUpdate();

            if (affectedRows == 0) {
                throw new SQLException("Creating album failed, no rows affected.");
            }
            try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    return generatedKeys.getInt(1);
                } else {
                    throw new SQLException("Creating album failed, no ID obtained.");
                }
            }
        }
    }

    public static void createNewAlbum(Connection db, String name, String description,
                                      Date releaseDate, List<Artist> artists, List<Song> songs) throws SQLException {
        for (Artist artist : artists) {
            if (ArtistDao.albumNameExists(db, artist, name))
                throw new SQLException("Album name already exists");

            for (Song song : songs) {
                if (ArtistDao.isSongInAlbumAlready(db, artist, song))
                    throw new SQLException("Song is already in an album by one of the artists");
            }
        }

        try {
//            db.beginTransaction();
            db.setAutoCommit(false);

            Album album = new Album(releaseDate, name, description);
            Integer albumId = AlbumDao.insert(db, album);

            for (Artist artist : artists) {
                AlbumArtistDao.insert(db, albumId, artist);
            }

            for (Song song : songs) {
                for (Artist artist : artists) {
                    SongArtistDao.insert(db, song, artist);
                }
                SongDao.updateAlbumId(db, song, albumId);
            }


            db.commit();
            db.setAutoCommit(true);
//            db.endTransaction();
        } catch (SQLException e) {
            db.rollback();
        }

    }

    public static void createNewAlbum_sp(Connection db, String name, String description,
                                         Date releaseDate, String artistIdList, String songIdList) throws SQLException {
        String sql = """
                EXEC createNewAlbum
                    @name = ?,
                    @description = ?,
                    @releaseDate = ?,
                    @artistList = ?,
                    @songList = ?
                """;
        CallableStatement statement = db.prepareCall(sql);
        statement.setString(1, name);
        statement.setString(2, description);
        statement.setDate(3, releaseDate);
        statement.setString(4, artistIdList);
        statement.setString(5, songIdList);
        statement.execute();
    }
}
