package dev.katussska;

import dev.katussska.dao.AlbumDao;
import dev.katussska.dto.Artist;
import dev.katussska.dto.Song;

import java.sql.Connection;
import java.sql.Date;
import java.sql.SQLException;
import java.util.List;
import com.microsoft.sqlserver.jdbc.SQLServerDriver;
import java.sql.DriverManager;

public class Main {
    public static void main(String[] args) {

        Connection db = null;
        try {
//            DriverManager.registerDriver(new SQLServerDriver());
//            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
            db = DriverManager.getConnection("jdbc:sqlserver://localhost:1433;databaseName=model", "sa", "kokos_123");
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
            e.printStackTrace();
        }
//        Database db = new Database();
//        db.connect();

        // vytvoreni alba
        try {
            AlbumDao.createNewAlbum(db,
                    "Testovaci album",
                    "Popis testovaciho alba",
                    new Date(2024, 5, 16),
                    List.of(new Artist(1), new Artist(2), new Artist(3)),
                    List.of(new Song(10), new Song(9), new Song(8)));
            System.out.println("Album vytvoreno");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }

        // album uz vytvoreno
        try {
            AlbumDao.createNewAlbum(db,
                    "Testovaci album",
                    "Popis testovaciho alba",
                    new Date(2024, 5, 16),
                    List.of(new Artist(1), new Artist(2), new Artist(3)),
                    List.of(new Song(10), new Song(9), new Song(8)));
            System.out.println("Album vytvoreno");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }

        // songs uz v jinem albu
        try {
            AlbumDao.createNewAlbum(db,
                    "Testovaci album2",
                    "Popis testovaciho alba2",
                    new Date(2024, 5, 16),
                    List.of(new Artist(2)),
                    List.of(new Song(10)));
            System.out.println("Album vytvoreno");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }

        // procedura
        try {
            AlbumDao.createNewAlbum_sp(db,
                    "Testovaci album222",
                    "Popis testovaciho alba2222",
                    new Date(2024, 5, 16),
                    "2",
                    "7");
            System.out.println("Album vytvoreno");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }

//        db.close();
    }
}