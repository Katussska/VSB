package dev.katussska.dto;

import lombok.*;

@Getter
@Setter
@NoArgsConstructor
public class Artist {
    private Integer artistId;
    private Integer userId;
    private String biography;
    private String name;
    private String country;

    public Artist(Integer artistId) {
        this.artistId = artistId;
    }
}
