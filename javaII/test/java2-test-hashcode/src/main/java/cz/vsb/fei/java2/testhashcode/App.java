package cz.vsb.fei.java2.testhashcode;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.stream.Stream;

import static cz.vsb.fei.java2.testhashcode.RectangleMath.RANDOM;

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
        int totalArea = Stream.generate(() -> new RectangleMath(new Point(RANDOM.nextInt(10), RANDOM.nextInt(10)), RANDOM.nextInt(10) + 1, RANDOM.nextInt(10) + 1))
                .limit(20)
                .mapToInt(RectangleMath::area)
                .sum();

        log.info("Total area of rectangles: " + totalArea);

        Stream.generate(Star::generate)
                .limit(20)
                .filter(star -> star.perimeter() < 30)
                .forEach(System.out::println);
    }

}