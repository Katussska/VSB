package cz.vsb.fei.java2.testhashcode;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.Random;
import java.util.stream.Stream;

/**
 * Class <b>App</b> - main class
 *
 * @author Java I
 */
public class App {

    private static final Logger log = LogManager.getLogger(App.class);

    public static void main(String[] args) {
        log.info("Launching Java application.");

        //TODO: generate streams
        int totalCredit = Stream.generate(() -> new CreditAccountMath(new Client("KOK", "JEZEBEL"), 5, 5))
                .limit(20)
                .mapToInt(CreditAccountMath::getCredit)
                .sum();

        Stream.generate(Interest::generate)
                .limit(20)
                .filter(e -> e.interest() > 5)
                .forEach(System.out::println);
    }

    public static int getRandomInt(int lowerLimit, int upperLimit) {
        return new Random().nextInt(upperLimit) + lowerLimit;
    }

    public static double getRandomDouble(double lowerLimit, double upperLimit) {
        return new Random().nextDouble(upperLimit) + lowerLimit;
    }
}