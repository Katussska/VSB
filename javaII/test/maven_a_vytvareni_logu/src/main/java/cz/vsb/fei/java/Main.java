package cz.vsb.fei.java;

import cz.vsb.fei.java.newPackage.NewClass;

import java.util.Random;

public class Main {
    public static void main(String[] args) {
        //2.4
        LoggerExample.generateLogs(getRandomInt(100, 200));

        new NewClass();
        new NewClass();
        new NewClass();
    }

    public static int getRandomInt(int lowerLimit, int upperLimit) {
        return new Random().nextInt(upperLimit + 1) + lowerLimit;
    }
}

