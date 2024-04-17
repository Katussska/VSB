package cz.vsb.fei.java;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.Random;

// 2.4
public class LoggerExample {
    private static final Logger logger = LogManager.getLogger(LoggerExample.class);
    private static final String[] levels = {"ERROR", "WARN", "INFO", "DEBUG"};

    public static void generateLogs(int numLogs) {


        for (int i = 0; i < numLogs; i++) {
            Random random = new Random();
            String level = levels[random.nextInt(levels.length)];
            switch (level) {
                case "ERROR":
                    logger.error("This is an error message");
                    break;
                case "WARN":
                    logger.warn("This is a warning message");
                    break;
                case "INFO":
                    logger.info("This is an info message");
                    break;
                case "DEBUG":
                    logger.debug("This is a debug message");
                    break;
            }
        }
    }
}
