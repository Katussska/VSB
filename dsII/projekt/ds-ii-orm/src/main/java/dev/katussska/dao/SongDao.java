package dev.katussska.dao;

import dev.katussska.Database;
import dev.katussska.dto.Song;

import java.sql.PreparedStatement;
import java.sql.SQLException;

public class SongDao {
    public static void insert(Database pDb, Song song) throws SQLException {
        Database db = Database.connect(pDb);
        String sql = """
                INSERT INTO song(release_date, duration, name, album_id, lyrics)
                VALUES (?, ?, ?, ?, ?)
                """;
        try (PreparedStatement statement = db.getConn().prepareStatement(sql)) {
            statement.setDate(1, song.getReleaseDate());
            statement.setString(2, song.getDuration());
            statement.setString(3, song.getName());
            statement.setInt(4, song.getAlbumId());
            statement.setString(5, song.getLyrics());
            int affectedRows = statement.executeUpdate();
            if (affectedRows == 0) {
                throw new SQLException("Creating album_artist failed, no rows affected.");
            }
        }
        Database.close(pDb, db);
    }
}
