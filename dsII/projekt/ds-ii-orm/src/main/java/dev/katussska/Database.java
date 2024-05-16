package dev.katussska;

import lombok.Getter;

import java.io.FileReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

@Getter
public class Database {
    private Connection conn;
    private final String dbUrl;
    private final String username;
    private final String password;

    public Database() {
        conn = null;
        Properties config;
        try {
            FileReader reader = new FileReader("application.properties");
            config = new Properties();
            config.load(reader);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        this.dbUrl = config.getProperty("db.url");
        this.username = config.getProperty("db.username");
        this.password = config.getProperty("db.password");
    }

    public void connect() {
        try {
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
            conn = DriverManager.getConnection(this.dbUrl);
//            conn = DriverManager.getConnection(dbUrl, username, password);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void beginTransaction() throws SQLException {
        if (conn != null) {
            conn.setAutoCommit(false);
        }
    }

    public void endTransaction() throws SQLException {
        if (conn != null) {
            conn.commit();
            conn.setAutoCommit(true);
        }
    }

    public void rollback() throws SQLException {
        if (conn != null) {
            conn.rollback();
        }
    }

    public void close() {
        if (conn != null) {
            try {
                conn.close();
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }
    }

    public static Database connect(Database pDb) {
        Database db;
        if (pDb == null) {
            db = new Database();
            db.connect();
        } else {
            db = pDb;
        }
        return db;
    }

    public static void close(Database pDb, Database db) {
        if (pDb == null) {
            db.close();
        }
    }
}