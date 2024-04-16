package cz.vsb.fei.java2.testhashcode;

import java.util.Random;

public record Interest(double interest, double balance) {
    static Random rand = new Random();

    public static Interest generate() {
        double randomNumber = rand.nextDouble(100) + 1;
        double randomNumber2 = rand.nextDouble(100) + 1;

        return new Interest(randomNumber, randomNumber2);
    }

    public double rate() {
        return 100 * interest / balance;
    }
}
