package dev.katussska;

import dev.katussska.dao.AlbumDao;
import dev.katussska.dto.Artist;
import dev.katussska.dto.Song;

import java.sql.Date;
import java.sql.SQLException;
import java.util.List;
import java.util.logging.Level;

public class Main {
    public static void main(String[] args) {
        Database db = new Database();
        db.connect();

        try {
            AlbumDao.createNewAlbum(db,
                    "Testovaci album",
                    "Popis testovaciho alba",
                    new Date(2024, 5, 16),
                    List.of(new Artist(1), new Artist(2), new Artist(3)),
                    List.of(new Song(10), new Song(9), new Song(8)));
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }

        db.close();
    }
}