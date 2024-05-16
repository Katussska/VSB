package dev.katussska.dao;

import dev.katussska.dto.Song;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class SongDao {
    public static void updateAlbumId(Connection db, Song song, int albumId) throws SQLException {
        String sql = """
                UPDATE song
                SET album_id = ?
                where song_id = ?
                                """;
        try (PreparedStatement statement = db.prepareStatement(sql)) {
            statement.setInt(1, albumId);
            statement.setInt(2, song.getSongId());
            int affectedRows = statement.executeUpdate();

            if (affectedRows == 0) {
                throw new SQLException("Creating album_artist failed, no rows affected.");
            }
        }
    }
}
