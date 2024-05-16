package dev.katussska.dto;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.sql.Date;

@Getter
@Setter
@NoArgsConstructor
public class Song {
    private Integer songId;
    private Date releaseDate;
    private String duration;
    private String name;
    private Integer albumId;
    private String lyrics;

    public Song(Integer songId) {
        this.songId = songId;
    }
}
