package cz.vsb.fei.java2.testjpa.entities;

import cz.vsb.fei.java2.testjpa.Tools;
import lombok.Getter;
import lombok.Setter;

import java.time.LocalDateTime;

@Setter
@Getter
public class Bird {
    int id;
    String birdName;
    LocalDateTime timeOfLastObservation;
    Nest nest;

    public static Bird createRandom() {
        Bird bird = new Bird();
        bird.birdName = "Bird" + Tools.RANDOM.nextInt(100);
        bird.timeOfLastObservation = LocalDateTime.now();
        return bird;
    }
}
