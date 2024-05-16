package dev.katussska.dao;

import dev.katussska.dto.Artist;
import dev.katussska.dto.Song;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class SongArtistDao {
    public static void insert(Connection db, Song song, Artist artist) throws SQLException {
        String sql = """
                INSERT INTO song_artist(song_id, artist_id)
                VALUES (?, ?)
                """;
        try (PreparedStatement statement = db.prepareStatement(sql)) {
            statement.setInt(1, song.getSongId());
            statement.setInt(2, artist.getArtistId());
            int affectedRows = statement.executeUpdate();
            if (affectedRows == 0) {
                throw new SQLException("Creating album_artist failed, no rows affected.");
            }
        }
    }
}
