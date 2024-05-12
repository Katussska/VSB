package cz.vsb.fei.java2.testjpa.entities;

import cz.vsb.fei.java2.testjpa.Tools;
import lombok.Getter;
import lombok.Setter;

import java.util.List;

@Setter
@Getter
public class Nest {
    int id;
    double latitude;
    double longitude;
    List<Bird> birds;

    public static Nest createRandom() {
        Nest nest = new Nest();
        nest.latitude = 49.2 + Tools.RANDOM.nextDouble();
        nest.longitude = 16.6 + Tools.RANDOM.nextDouble();
        return nest;
    }
}
