package cz.vsb.fei.java2.testjpa.entities;

import cz.vsb.fei.java2.testjpa.Tools;

import java.time.LocalDateTime;

public class StormObservation {
    int id;
    LocalDateTime whenObserved;
    String cityOfObservation;
    double latitude;
    double longitude;

    public static StormObservation createRandom() {
        StormObservation so = new StormObservation();
        so.whenObserved = LocalDateTime.now();
        so.cityOfObservation = Tools.CITIES.get(Tools.RANDOM.nextInt(Tools.CITIES.size()));
        so.latitude = 49.2 + Tools.RANDOM.nextDouble();
        so.longitude = 16.6 + Tools.RANDOM.nextDouble();
        return so;
    }
}
