package dev.katussska.dao;

import dev.katussska.Database;
import dev.katussska.dto.Artist;

import java.sql.PreparedStatement;
import java.sql.SQLException;

public class AlbumArtistDao {
    public static void insert(Database pDb, Integer albumId, Artist artist) throws SQLException {
        Database db = Database.connect(pDb);
        String sql = """
                INSERT INTO album_artist(album_id, artist_id)
                VALUES (?, ?)
                """;
        try (PreparedStatement statement = db.getConn().prepareStatement(sql)) {
            statement.setInt(1, albumId);
            statement.setInt(2, artist.getArtistId());
            int affectedRows = statement.executeUpdate();
            if (affectedRows == 0) {
                throw new SQLException("Creating album_artist failed, no rows affected.");
            }
        }
        Database.close(pDb, db);
    }
}
