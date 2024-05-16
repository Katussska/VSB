package dev.katussska.dto;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.sql.Date;

@Getter
@Setter
@NoArgsConstructor
public class Album {
    private Integer albumId;
    private Date releaseDate;
    private String name;
    private String description;

    public Album(Date releaseDate, String name, String description) {
        this.releaseDate = releaseDate;
        this.name = name;
        this.description = description;
    }
}
