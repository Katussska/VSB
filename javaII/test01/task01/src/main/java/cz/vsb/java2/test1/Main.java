package cz.vsb.java2.test1;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.Random;

import static cz.vsb.java2.test1.logging.Louger.logging;

/*
TRACE
DEBUG
INFO
WARN
ERROR
FATAL
 */

public class Main {

    private static final Logger logger = LogManager.getLogger(Main.class);
    private static final Random random = new Random();

    public static void main(String[] args) {
        for (int i = 0; i < 15; i++) {
            message_logger();
        }

        logging();
    }

    private static void message_logger() {
        int randomNumber = random.nextInt(6);
        switch (randomNumber) {
            case 0:
                logger.trace("This is an trace message.");
                break;
            case 1:
                logger.debug("This is a debug message.");
                break;
            case 2:
                logger.info("This is an info message.");
                break;
            case 3:
                logger.warn("This is an warn message.");
                break;
            case 4:
                logger.error("This is an error message.");
                break;
            case 5:
                logger.fatal("This is an fatal message.");
                break;
        }
    }
}