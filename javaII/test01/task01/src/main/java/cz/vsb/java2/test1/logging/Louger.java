package cz.vsb.java2.test1.logging;

import cz.vsb.java2.test1.Main;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class Louger {
    private static final Logger logger = LogManager.getLogger(Main.class);

    public static void logging() {
        logger.warn("This is an warn message. S");
        logger.warn("This is an warn message. X");
        logger.warn("This is an warn message. C");
        logger.warn("This is an warn message. B");
    }
}
