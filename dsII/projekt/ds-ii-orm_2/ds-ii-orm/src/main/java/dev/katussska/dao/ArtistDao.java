package dev.katussska.dao;

import dev.katussska.dto.Artist;
import dev.katussska.dto.Song;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ArtistDao {
    public static boolean albumNameExists(Connection db, Artist artist, String albumName) throws SQLException {
        String sql = """
                SELECT COUNT(1) AS album_count
                FROM album al
                    JOIN album_artist aa ON aa.album_id = al.album_id
                    JOIN artist ar ON ar.artist_id = aa.artist_id
                WHERE al.name = ?
                    AND ar.artist_id = ?
                """;
        try (PreparedStatement statement = db.prepareStatement(sql)) {
            statement.setString(1, albumName);
            statement.setInt(2, artist.getArtistId());
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt("album_count") > 0;
                }
            }
        }
        return false;
    }

    public static boolean isSongInAlbumAlready(Connection db, Artist artist, Song song) throws SQLException {
        String sql = """
                SELECT COUNT(1) AS song_count
                FROM artist ar
                    JOIN album_artist aa ON ar.artist_id = aa.artist_id
                    JOIN album a ON aa.album_id = a.album_id
                    JOIN song s ON a.album_id = s.album_id
                WHERE s.song_id = ?
                    AND ar.artist_id = ?
                """;
        try (PreparedStatement statement = db.prepareStatement(sql)) {
            statement.setInt(1, song.getSongId());
            statement.setInt(2, artist.getArtistId());
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next())
                    return resultSet.getInt("song_count") > 0;
            }
        }
        return false;
    }
}
