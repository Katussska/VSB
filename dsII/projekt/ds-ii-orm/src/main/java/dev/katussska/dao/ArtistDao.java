package dev.katussska.dao;

import dev.katussska.Database;
import dev.katussska.dto.Artist;
import dev.katussska.dto.Song;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ArtistDao {
    public static boolean albumNameExists(Database pDb, Artist artist, String albumName) throws SQLException {
        Database db = Database.connect(pDb);
        String sql = """
                SELECT COUNT(1) AS album_count
                FROM album al
                    JOIN album_artist aa ON aa.album_id = al.album_id
                    JOIN artist ar ON ar.artist_id = aa.artist_id
                WHERE al.name = ?
                    AND ar.artist_id = ?
                """;
        try (PreparedStatement statement = db.getConn().prepareStatement(sql)) {
            statement.setString(1, albumName);
            statement.setInt(2, artist.getArtistId());
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    Database.close(pDb, db);
                    return resultSet.getInt("album_count") > 0;
                }
            }
        }
        Database.close(pDb, db);
        return false;
    }

    public static boolean isSongInAlbumAlready(Database pDb, Artist artist, Song song) throws SQLException {
        Database db = Database.connect(pDb);
        String sql = """
                SELECT COUNT(1) AS song_count
                FROM artist ar
                    JOIN album_artist aa ON ar.artist_id = aa.artist_id
                    JOIN album a ON aa.album_id = a.album_id
                    JOIN song s ON a.album_id = s.album_id
                WHERE s.name = ?
                    AND ar.artist_id = ?
                """;
        try (PreparedStatement statement = db.getConn().prepareStatement(sql)) {
            statement.setString(1, song.getName());
            statement.setInt(2, artist.getArtistId());
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next())
                    return resultSet.getInt("song_count") > 0;
            }
        }
        Database.close(pDb, db);
        return false;
    }
}
